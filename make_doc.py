import os
import re
from enum import Flag, auto


class Lang(Flag):
    UNK = 0
    PY = auto()
    SW = auto()
    C = auto()
    CPP = auto()


c_langs = {"c": Lang.C, "cpp": Lang.CPP, "py": Lang.PY, "swift": Lang.SW}
c_lang_img = {Lang.C: "c", Lang.CPP: "cpp", Lang.PY: "py", Lang.SW: "sw"}

problems = {}
g_filesCnt = 0
g_unsolved = 0

rexDir = re.compile("\\d{2,4}")  # Directory must be in form DD or DDDD
rexFile = re.compile("m(\\d+).*\\.(\\w+)")  # Filename must be in correct form
rexComment = re.compile(r"\s*(/{2,}|#+)\s*")
rexSolved = re.compile("solved", flags=re.I)
rexDescr = re.compile("\\(([E|M|H])\\)\\s+(.+)")
rexLink = re.compile("(https:.+)")
rexHelper = re.compile(r"helper:\s*(.*)", flags=re.I)
rexTemplate = re.compile("\\{block:(\\w+)\\}")


def readDescription(fileName: str, line: str, details: dict) -> bool:
    match = rexDescr.match(line)
    if match:
        if "difficulty" in details:
            if details["difficulty"] != match[1]:
                print(f"Difficulty of the problem in {fileName} differs from other files in dir")
        else:
            details["difficulty"] = match[1]

        if "name" in details:
            if details["name"] != match[2]:
                print(f"Name of the problem in {fileName} differs from other files in dir")
        else:
            details["name"] = match[2]

        return True
    return False

def readLink(fileName: str, line: str, details: dict) -> bool:
    match = rexLink.match(line)
    if match:
        if "link" in details:
            if details["link"] != match[1]:
                print(f"Leetcode link in {fileName} differs from other files in dir")
        else:
            details["link"] = match[1]

        return True
    return False


def readHelper(fileName: str, line: str, details: dict, lang: Lang) -> bool:
    match = rexHelper.match(line)
    if match:
        data = (lang, "https://github.com/chemandante/leetcode/blob/master" + fileName[1:], match[1])
        if "helper" in details:
            details["helper"].append(data)
        else:
            details["helper"] = [data]
        return True
    return False


def readDetails(fileName: str, details: dict, lang: Lang) -> bool:
    global g_filesCnt, g_unsolved

    g_filesCnt += 1

    # Try to find correct comments
    with open(fileName, "r", encoding="utf8") as f:
        isSolved = False
        i = 0
        for line in f:
            match = rexComment.match(line)
            if match:
                line = line[match.span()[1]:]
                if isSolved:
                    # Try to find correct description
                    if readDescription(fileName, line, details):
                        continue
                    # Try to find leetcode link
                    if readLink(fileName, line, details):
                        continue
                    # Try to read helpers
                    if readHelper(fileName, line, details, lang):
                        continue
                else:
                    match = rexSolved.match(line)
                    if match:
                        isSolved = True
                        continue

            i += 1
            if i > 5:
                break

    if not isSolved:
        g_unsolved += 1

    return isSolved


def getProblemDetails(prNum: int, dir: str) -> dict:
    details = {"lang": Lang.UNK}

    for fileName in os.listdir(dir):
        match = rexFile.fullmatch(fileName)
        fullName = f"{dir}/{fileName}"
        if os.path.isfile(fullName) and match:
            # Check for problem number correctness
            if int(match[1]) == prNum:
                # Check the language
                lang = c_langs.get(match[2], Lang.UNK)
                if lang != lang.UNK:
                    if readDetails(fullName, details, lang):
                        details["lang"] |= lang
                    else:
                        print(f"'{fullName}' not solved yet")
                else:
                    print(f"Unknown file '{fileName}' found in '{dir}'")
            else:
                print(f"Strange file '{fileName}' found in '{dir}'")

    return details


def EnumerateProblems():
    for dir1 in os.listdir("."):
        # For directory NN
        if os.path.isdir(dir1) and rexDir.fullmatch(dir1):
            # For dir1 in form DD
            if len(dir1) == 2:
                prPreNum = 100 * int(dir1)
                for dir2 in os.listdir("./" + dir1):
                    subDir = f"./{dir1}/{dir2}"
                    # For directory MM
                    if os.path.isdir(subDir) and rexDir.fullmatch(dir2):
                        prNum = prPreNum + int(dir2)
                        problems[prNum] = getProblemDetails(prNum, subDir)
            else:  # There are no any subfolders for dir1 containing more than 2 digits
                prNum = int(dir1)
                problems[prNum] = getProblemDetails(prNum, f"./{dir1}")


    for k, v in sorted(problems.items()):
        if "name" not in v:
            print(f"No correct description found for problem {k}")
            problems[k] = None

    if g_unsolved:
        print(f"{g_unsolved} {'file' if g_unsolved == 1 else 'files'} out of {g_filesCnt} "
              f"{'is' if g_unsolved == 1 else 'are'} unsolved yet ({g_unsolved * 100 / g_filesCnt:.0f}%)")


EnumerateProblems()


with open("index.template.md", "r", encoding="utf8") as fTemplate:
    with open("docs/index.md", "w", encoding="utf8") as fOut:
        for line in fTemplate.readlines():
            match = rexTemplate.match(line)
            if match:
                # Filling table with problems
                if match[1] == "problems":
                    for k, v in sorted(problems.items()):
                        if v:
                            strDifficultyImage = f"![{v['difficulty']}](img/{v['difficulty']}.png)"
                            strLeetcodeLink = f"[{v['name']}]({v['link']})"
                            strLangs = ""
                            langs = v["lang"]
                            for flag in Lang:
                                if flag & langs:
                                    strLangs += f"![](img/{c_lang_img[flag]}.png) "
                            strRow = f"| {k} | {strDifficultyImage} {strLeetcodeLink} | | {strLangs}|\n"
                            fOut.write(strRow)
                elif match[1] == "helpers":
                    for k, v in sorted(problems.items()):
                        if v and "helper" in v:
                            for hlp in v["helper"]:
                                strLink = f"<a href=\"{hlp[1]}\" target=\"_blank\">"\
                                          f"<img src=\"img/{c_lang_img[hlp[0]]}.png\"></a>"
                                strRow = f"| {hlp[2]} | {k}. {v['name']} {strLink} |\n"
                                fOut.write(strRow)
            else:
                fOut.write(line)
