import os
import re
from collections import defaultdict
from enum import Flag, auto


class Lang(Flag):
    UNK = 0
    PY = auto()
    SW = auto()
    C = auto()
    CPP = auto()


c_langs = {"c": Lang.C, "cpp": Lang.CPP, "py": Lang.PY, "swift": Lang.SW}
c_lang_img = {Lang.C: "c", Lang.CPP: "cpp", Lang.PY: "py", Lang.SW: "sw"}
c_github_blob = "https://github.com/chemandante/leetcode/blob/master"
c_github_tree = "https://github.com/chemandante/leetcode/tree/master"
c_algorithms = {"BINS": "Binary search"}

problems = {}
algorithms = defaultdict(dict)
algorithms["UNK"] = list()
g_filesCnt = 0
g_unsolved = 0

rexDir = re.compile(r"\d{2,4}")  # Directory must be in form DD or DDDD
rexFile = re.compile(r"m(\d+).*\.(\w+)")  # Filename must be in correct form
rexComment = re.compile(r"\s*(/{2,}|#+)\s*")
rexSolved = re.compile("solved", flags=re.I)
rexDescr = re.compile(r"\(([EMH])\)\s+(.+)")
rexLink = re.compile(r"(https:.+)")
rexHelper = re.compile(r"helper:\s*(.*)", flags=re.I)
rexAlgo = re.compile(r"([A-Z]+):\s+(.+)")
rexTemplate = re.compile(r"\{block:(\w+)}")


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


def readAlgo(prNum, fileName: str, line: str):
    match = rexAlgo.match(line)
    if match:
        if match[1] in c_algorithms:
            algorithms[match[1]][prNum] = match[2]
        else:
            algorithms["UNK"].append((match[1], fileName))
        pass


def readHelper(fileName: str, line: str, details: dict, lang: Lang) -> bool:
    match = rexHelper.match(line)
    if match:
        data = (lang, fileName, match[1])
        if "helper" in details:
            details["helper"].append(data)
        else:
            details["helper"] = [data]
        return True
    return False


def readDetails(prNum: int, fileName: str, details: dict, lang: Lang) -> bool:
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
                    # Try to read algorithm description
                    if readAlgo(prNum, fileName, line):
                        continue
                    # Try to read helpers
                    if readHelper(fileName, line, details, lang):
                        continue
                else:
                    if rexSolved.match(line):
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
                    if readDetails(prNum, fullName, details, lang):
                        details["lang"] |= lang
                        if "solution" in details:
                            details["solution"][lang] = fullName
                        else:
                            details["solution"] = {lang: fullName}
                    else:
                        print(f"'{fullName}' not solved yet")
                else:
                    print(f"Unknown file '{fileName}' found in '{dir}'")
            else:
                print(f"Strange file '{fileName}' found in '{dir}'")

    return details


def makeGithubBlobLink(fileName: str, lang: Lang) -> str:
    strFileLink = c_github_blob + fileName[1:]
    return f"<a href=\"{strFileLink}\" target=\"_blank\"><img src=\"img/{c_lang_img[lang]}.png\"></a>"


def makeGithubTreeLink(dirName: str, text: str) -> str:
    strFileLink = c_github_tree + dirName[1:]
    return f"<a href=\"{strFileLink}\" target=\"_blank\">{text}</a>"


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
                        problems[prNum]["subdir"] = subDir
            else:  # There are no any subfolders for dir1 containing more than 2 digits
                subDir = f"./{dir1}"
                prNum = int(dir1)
                problems[prNum] = getProblemDetails(prNum, subDir)
                problems[prNum]["subdir"] = subDir


    for k, v in sorted(problems.items()):
        if "name" not in v:
            print(f"No correct description found for problem {k}")
            problems[k] = None

    if g_unsolved:
        print(f"{g_unsolved} {'file' if g_unsolved == 1 else 'files'} out of {g_filesCnt} "
              f"{'is' if g_unsolved == 1 else 'are'} unsolved yet ({g_unsolved * 100 / g_filesCnt:.0f}%)")

    if len(algorithms["UNK"]) > 0:
        print(f"{len(algorithms['UNK'])} unknown algorithm descriptions found:")
        for d in algorithms["UNK"]:
            print(f"\t'{d[0]}' in {d[1]}")


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
                                    strLangs += makeGithubBlobLink(v["solution"][flag], flag) + " "
                            strRow = f"| {k} | {strDifficultyImage} {strLeetcodeLink} | | {strLangs}|\n"
                            fOut.write(strRow)

                elif match[1] == "helpers":
                    for k, v in sorted(problems.items()):
                        if v and "helper" in v:
                            for hlp in v["helper"]:
                                strLink = makeGithubBlobLink(hlp[1], hlp[0])
                                strRow = f"| {hlp[2]} | {k}. {v['name']} {strLink} |\n"
                                fOut.write(strRow)

                elif match[1] == "algo":
                    for k, v in c_algorithms.items():
                        if len(algorithms[k]) > 0:
                            fOut.write(f"#### {v}\n\n")
                            fOut.write("| No. | Solutions where implemented | Lang | Notes |\n"
                                       "|:---:|-----------------------------|:----:|-------|\n")
                            for prNum, desc in sorted(algorithms[k].items()):
                                details = problems[prNum]
                                strLink = makeGithubTreeLink(details["subdir"], details['name'])
                                strLangs = ""
                                langs = details["lang"]
                                for lang in Lang:
                                    if lang & langs:
                                        strLangs += f"![](img/{c_lang_img[lang]}.png) "
                                fOut.write(f"| {prNum} | {strLink} | {strLangs}| {desc} |\n")

            else:
                fOut.write(line)
