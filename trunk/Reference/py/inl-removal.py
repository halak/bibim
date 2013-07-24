# -*- coding:utf-8 -*-

import glob
import os

MODULES = (
    'Animation',
    'Asset',
    'Audio',
    'Collision2D',
    'Component',
    'Diagnostics',
    'FileSystem',
    'Foundation',
    'Framework',
    'Gameplay',
    'GFX',
    'Graphics',
    'Input',
    'IPC',
    'Module',
    'Net',
    'Scripting',
    'Startup',
    'Threading',
    'Time',
    'Typography',
    'UI',
)

def readfile(path):
    f = open(path, 'r')
    s = f.read()
    if (len(s) >= 3 and s[0] == '\xEF' and s[1] == '\xBB' and s[2] == '\xBF'):
        s = s[3:]
    f.close()
    
    return s
    
def writefile(path, s):
    f = open(path, 'w')
    f.write('\xEF')
    f.write('\xBB')
    f.write('\xBF')
    f.write(s)
    f.close()

def process(h, inl):
    inline = readfile(inl).strip();    
    if (inline.startswith('namespace Bibim\n{\n')):
        inline = inline[len('namespace Bibim\n{\n'):]
    if (inline.endswith('\n}')):
        inline = inline[:len(inline) - len('\n}')]
        
    inline = '        ////////////////////////////////////////////////////////////////////////////////////////////////////\n\n' + inline
    inline = inline.replace('\n    ', '\n        ')
    # print(inline)
    
    header = readfile(h)
    index = header.rfind('    }')
    
    a = header[:index]
    b = header[index:]
    
    header = a + '\n' + inline + '\n' + b
    #print(header)
    writefile(h, header)
    os.remove(inl)
        
if (__name__ == '__main__'):
    for item in MODULES:
        src = './{0}/Bibim/'.format(item)
        names = os.listdir(src)
        
        for name in names:
            components = os.path.splitext(name)
            if (components[1] == '.inl'):
                process(src + components[0] + '.h', src + name)
    #process('./Animation/Bibim/EvalBinaryOperators.h', './Animation/Bibim/EvalBinaryOperators.inl')