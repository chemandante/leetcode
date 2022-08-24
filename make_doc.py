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
rexDir = re.compile("\\d{2}")  # Directory must be in form DD
rexFile = re.compile("m(\\d+)\\.(\\w+)")  # Filename must be in correct form
rexSolved = re.compile("\\s*(//|#)\\s*solved", flags=re.I)  # \\(([A-Z])\\) (.+)")
rexDescr = re.compile("\\s*(//|#)\\s*\\(([E|M|H])\\)\\s+(.+)")
rexLink = re.compile("\\s*(//|#)\\s*(https:.+)")
rexTemplate = re.compile("\\{block:(\\w+)\\}")


def readDetails(fileName: str, lang: Lang, details: dict) -> bool:
    # Try to find correct comments
    with open(fileName, "r", encoding="utf8") as f:
        isSolved = False
        i = 0
        for line in f:
            if isSolved:
                # Try to find correct description
                match = rexDescr.match(line)
                if match:
                    if "difficulty" in details:
                        if details["difficulty"] != match[2]:
                            print(f"Difficulty of the problem in {fileName} differs from other files in dir")
                    else:
                        details["difficulty"] = match[2]

                    if "name" in details:
                        if details["name"] != match[3]:
                            print(f"Name of the problem in {fileName} differs from other files in dir")
                    else:
                        details["name"] = match[3]

                    continue
                # Try to find leetcode link
                match = rexLink.match(line)
                if match:
                    if "link" in details:
                        if details["link"] != match[2]:
                            print(f"Leetcode link in {fileName} differs from other files in dir")
                    else:
                        details["link"] = match[2]

            else:
                match = rexSolved.match(line)
                if match:
                    isSolved = True

            i += 1
            if i > 6:
                break

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
                    if readDetails(fullName, lang, details):
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
            prPreNum = 100 * int(dir1)
            for dir2 in os.listdir("./" + dir1):
                subDir = f"./{dir1}/{dir2}"
                # For directory MM
                if os.path.isdir(subDir) and rexDir.fullmatch(dir2):
                    prNum = prPreNum + int(dir2)
                    details = getProblemDetails(prNum, subDir)
                    problems[prNum] = details

    for k, v in sorted(problems.items()):
        if "name" not in v:
            print(f"No correct description found for problem {k}")
            problems[k] = None


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
                            strRow = f"| {k} | {strDifficultyImage} {strLeetcodeLink} | | {strLangs} |\n"
                            fOut.write(strRow)
                        else:
                            print(f"Problem {k} not solved yet at all")
            else:
                fOut.write(line)
