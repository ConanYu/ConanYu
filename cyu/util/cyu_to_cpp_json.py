import os, json

def StrToDict(code: str, title: str) -> dict:
  def FilterFunc(s: str):
    if s == '':
      return False
    if '#pragma once' in s:
      return False
    if '#include' in s:
      return False
    return True

  code = filter(FilterFunc, '\r'.join(code.split('\n')).split('\r'))
  ret = dict()
  ret['prefix'] = title
  ret['description'] = title
  ret['body'] = list(code)
  return ret

res = dict()

for path, _, files in os.walk(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))):
  for file in files:
    if os.path.splitext(file)[-1] in {'.hpp', '.h', '.c', '.cpp'}:
      name = os.path.splitext(file)[0]
      with open(os.path.join(path, file), 'r', encoding='utf-8') as f:
        assert(res.get(name) is None)
        res[name] = StrToDict(f.read(), name)

with open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'cyu.cpp.json'), 'w', encoding='utf-8') as f:
  f.write(json.dumps(res))
