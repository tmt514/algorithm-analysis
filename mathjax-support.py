#!/usr/bin/env python3

import json
import sys
import re

if len(sys.argv) > 1:
    if sys.argv[1] == 'supports':
        # sys.argv[2] is the renderer name
        sys.exit(0)

context, book = json.load(sys.stdin)

p = re.compile(r'([^$]|^)\$(?P<inner>[^$]+)\$(?=[^$]|$)')
q = re.compile(r'([^$]|^)\$\$(?P<inner>[^$]+)\$\$(?=[^$]|$)')
mid = re.compile(r'([^|])\|')

def inner_replace_rules(inner):
  inner = inner.replace(r'\\', r'\\\\')
  inner = inner.replace(r'\{', r'\\{')
  inner = inner.replace(r'\}', r'\\}')
  inner = mid.sub(r'\1\\vert ', inner)
  inner = inner.replace('_', r'\_')
  inner = inner.replace('*', r'\*')
  return inner
    
def handle_chapter(chapter):
  sys.stderr.write("Chapter: " + chapter["name"] + "\n")
  content = chapter["content"]
  
  # Substitutes single dollar sign to \\( and \\).
  result = ""
  start = 0
  for match in p.finditer(content):
    l, r = match.span()
    # sys.stderr.write(str(match) + "\n")
    result += content[start : l]
    result += match.group(1)
    result += r"\\("
    inner = match.group(2)
    inner = inner_replace_rules(inner)
    result += inner
    result += r"\\)"
    start = r
  result += content[start:]
  
  # Substitutes double dollar sign pair to \\[ and \\].
  content = result
  result = ""
  start = 0
  for match in q.finditer(content):
    l, r = match.span()
    # sys.stderr.write(str(match) + "\n")
    result += content[start : l]
    result += match.group(1)
    result += "\\\\["
    inner = match.group(2)
    inner = inner_replace_rules(inner)
    result += inner
    result += "\\\\]"
    start = r
  result += content[start:]
  
  # result = p.sub(r'\1\\\\(\g<inner>\\\\)\3', content)
  # sys.stderr.write(result[:500] + "\n\n")
  # Modify content to the substituted results.
  chapter["content"] = result
  
  
  for sub_item in chapter["sub_items"]:
    sub_chapter = sub_item["Chapter"]
    handle_chapter(sub_chapter)

sections = book["sections"]
for section in sections:
  chapter = section["Chapter"]
  handle_chapter(chapter)
  
  # sys.stderr.write("Chapter %d\n" % i)
  # sys.stderr.write("\n".join(list(chapter.keys())))
  # sys.stderr.write(json.dumps(chapter, indent=2))
json.dump(book, sys.stdout)