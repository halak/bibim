# -*- coding:utf-8 -*-
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
    'IO',
    'Graphics',
    'Input',
    'Module',
    'Net',
    'Scripting',
    'Threading',
    'Time',
    'Typography',
    'UI',
)

def file_ext(filename):
    return os.path.splitext(filename)[1][1:]

class PLATFORM:
    WIN32 = 1
    ANDROID = 2
    IOS = 3
    EMSCRIPTEN = 4

    @staticmethod
    def to_string(code):
        if code == PLATFORM.WIN32:
            return 'Win32'
        elif code == PLATFORM.ANDROID:
            return 'Android'
        elif code == PLATFORM.IOS:
            return 'iOS'
        elif code == PLATFORM.EMSCRIPTEN:
            return 'Emscripten'
        else:
            return None

    
class TARGET:
    DEBUG = 1
    RELEASE = 2
    
    @staticmethod
    def to_string(code):
        if code == TARGET.DEBUG:
            return 'Debug'
        elif code == TARGET.RELEASE:
            return 'Release'
        else:
            return None
    
    
class ENVIRONMENT:
    VS2008 = 1
    VS2010 = 2
    VS2013 = 3

    @staticmethod
    def to_string(code):
        if code == ENVIRONMENT.VS2008:
            return 'vs2008'
        elif code == ENVIRONMENT.VS2010:
            return 'vs2010'
        elif code == ENVIRONMENT.VS2013:
            return 'vs2013'
        else:
            return None
    
    
def get_include_directories(environment, platform, target):
    l = []
    l += ['$(BIBIM_DIR)include']

    if platform == PLATFORM.WIN32:
        l += ['$(DXSDK_DIR)Include']
    
    return l
    
    
def get_library_directories(environment, platform, target):
    l = []

    if platform == PLATFORM.WIN32:
        l += ['$(DXSDK_DIR)Lib/x86']
        l += ['$(BIBIM_DIR)extlibs/irrKlang-1.4.0/lib/Win32-visualStudio']
    
    return l    

    
def get_dependencies(environment, platform, target):
    l = []
    win32 = platform == PLATFORM.WIN32
    android = platform == PLATFORM.ANDROID
    ios = platform == PLATFORM.IOS
    emscripten = platform == PLATFORM.EMSCRIPTEN
    debug = target == TARGET.DEBUG
    release = target == TARGET.RELEASE
    vs2008 = environment == ENVIRONMENT.VS2008
    vs2010 = environment == ENVIRONMENT.VS2010
    vs2013 = environment == ENVIRONMENT.VS2013

    # BIBIM
    if win32:
        l += ['Bibim.lib']
    elif android:
        l += ['Bibim.a']
    elif emscripten:
        l += ['Bibim.bc']
    
    # Platform
    if win32:
        l += ['winmm.lib']
        l += ['ws2_32.lib']
    
    # DirectX9
    if win32:
        l += ['d3d9.lib']
        if debug:
            l += ['d3dx9d.lib']
        elif release:
            l += ['d3dx9.lib']
     
    # ZLib & PNG & JPG & FreeType & Lua
    if win32:
        l += ['libpng.lib', 'libjpeg.lib', 'freetype.lib', 'lua.lib', 'zlib.lib']
    elif android:
        l += ['libpng.a', 'libjpeg.a', 'freetype.a', 'lua.a', 'zlib.a']
    elif emscripten:
        l += ['libpng.bc', 'libjpeg.bc', 'freetype.bc', 'lua.bc', 'zlib.bc']
    
    # irrKlang
    if win32:
        l += ['irrKlang.lib']
        
    # OpenAL
    # if win32:
    #     l += ['OpenAL32.lib']
    # elif android:
    #     l += ['libopenal.so']
    #     l += ['libopenalwrapper.so']
        
    # MPQ
    if win32:
        if debug:
            l += ['StormLibDAD.lib']
        elif release:
            l += ['StormLibRAD.lib']

    return l
        

def save_xml(filename, element):
    import xml.etree.ElementTree as ET
    xml_text = ET.tostring(element, 'utf-8')
    
    f = open(filename, 'wb')
    f.write('<?xml version="1.0" encoding="utf-8"?>\n'.encode('utf-8'))
    f.write(xml_text)
    f.close()
    
    
def get_main_library_directory(environment, platform, target):    
    environment = ENVIRONMENT.to_string(environment)
    platform = PLATFORM.to_string(platform)
    target = TARGET.to_string(target)
    
    components = ['lib']
    if environment:
        components.append(environment)
    if platform:
        components.append(platform)
    if target:
        components.append(target)

    return os.path.join(*components)


def make_visual_studio_2008_property_sheet(name, 
                                           include_directories,
                                           library_directories,
                                           depdendencies,
                                           target):
                                     
    import xml.etree.ElementTree as ET
    root = ET.Element('VisualStudioPropertySheet', {
        'ProjectType': 'Visual C++',
        'Version': '8.00',
        'Name': name,
    })
    
    root.append(ET.Element('Tool', {
        'Name': 'VCCLCompilerTool',
        'AdditionalIncludeDirectories': include_directories.replace('/', '\\'),
        'PreprocessorDefinitions': '',
        'WarningLevel': '4',
    }))
    root.append(ET.Element('Tool', {
        'Name': 'VCLinkerTool',
        'AdditionalDependencies': depdendencies.replace('/', '\\').replace(';', ' '),
        'AdditionalLibraryDirectories': library_directories.replace('/', '\\'),
    }))
    
    return root
    
    
def make_visual_studio_2010_property_sheet(name,
                                           include_directories,
                                           library_directories,
                                           depdendencies,
                                           target,
                                           platform):
    
    import xml.etree.ElementTree as ET
    root = ET.Element('Project', {
        'DefaultTargets': 'Build',
        'ToolsVersion': '4.0',
        'xmlns': 'http://schemas.microsoft.com/developer/msbuild/2003',
    })
    
    def ETElementWithText(element, text):
        element = ET.Element(element)
        element.text = text
        return element
    
    property_group = ET.Element('PropertyGroup')
    property_group.append(ETElementWithText(
        '_ProjectFileVersion_ProjectFileVersion',
        '10.0.40219.1'
    ))
    root.append(property_group)
    
    item_definition_group = ET.Element('ItemDefinitionGroup')
    cl_compile = ET.Element('ClCompile')
    cl_compile.append(ETElementWithText(
        'AdditionalIncludeDirectories',
        include_directories.replace('/', '\\') + ';%(AdditionalIncludeDirectories)'
    ))
    cl_compile.append(ETElementWithText('WarningLevel', 'Level4'))

    if target == TARGET.DEBUG and platform == PLATFORM.ANDROID:
        cl_compile.append(ETElementWithText('PreprocessorDefinitions', '_DEBUG'))

    item_definition_group.append(cl_compile)
    link = ET.Element('Link')
    link.append(ETElementWithText(
        'AdditionalDependencies',
        depdendencies.replace('/', '\\') + ';%(AdditionalDependencies)'
    ))
    link.append(ETElementWithText(
        'AdditionalLibraryDirectories',
        library_directories.replace('/', '\\') + ';%(AdditionalLibraryDirectories)'
    ))
    if platform == PLATFORM.ANDROID:
        link.append(ETElementWithText(
            'AdditionalOptions',
            '-lGLESv2 -landroid %(AdditionalOptions)'
        ))
    item_definition_group.append(link)
    root.append(item_definition_group)
    
    return root
    
    
def publish_library(environment, platform, target):
    name = 'Bibim'
    main_library_rel_directory = get_main_library_directory(environment, platform, target)
    main_library_abs_directory = '$(BIBIM_DIR){0}'.format(main_library_rel_directory)
    
    # 추가 포함 디렉터리와 라이브러리 디렉터리를 구합니다.
    include_directories = get_include_directories(environment, platform, target)
    include_directory = ';'.join(map(lambda o: '"{0}"'.format(o), include_directories))
    library_directories = [main_library_abs_directory]
    library_directories += get_library_directories(environment, platform, target)
    library_directory = ';'.join(map(lambda o: '"{0}"'.format(o), library_directories))
        
    # 의존 라이브러리들 목록을 구합니다.
    dependencies = get_dependencies(environment, platform, target)
    if platform == PLATFORM.ANDROID or platform == PLATFORM.EMSCRIPTEN:
        dependency_filenames = ';'.join(map(
            lambda o: os.path.join(main_library_abs_directory, os.path.basename(o)),
            dependencies
        ))
    else:
        dependency_filenames = ';'.join(map(
            lambda o: os.path.basename(o),
            dependencies
        ))
    
    # 환경에 맞는 프로퍼티 시트를 생성해서 저장합니다.
    if environment == ENVIRONMENT.VS2008:
        element = make_visual_studio_2008_property_sheet(name,
                                                         include_directory,
                                                         library_directory,
                                                         dependency_filenames,
                                                         target)
        save_xml('{0}.vsprops'.format(os.path.join(main_library_rel_directory, name)), element)
    elif environment == ENVIRONMENT.VS2010 or environment == ENVIRONMENT.VS2013:
        element = make_visual_studio_2010_property_sheet(name,
                                                         include_directory,
                                                         library_directory,
                                                         dependency_filenames,
                                                         target,
                                                         platform)
        save_xml('{0}.props'.format(os.path.join(main_library_rel_directory, name)), element)


def merge_sources(directory):
    from datetime import datetime

    lines = []
    lines.append('// Automatically generated in {0}'.format(datetime.now()))
    lines.append('')
    lines.append('#include <zlib.h>')
    for module in MODULES:
        for item in os.listdir(os.path.join(directory, module)):
            if file_ext(item) == 'cpp':
                lines.append('#include "{0}/{1}"'.format(module, item))

    f = open(os.path.join(directory, 'Bibim.cpp'), 'w')
    f.write('\n'.join(lines))
    f.close()
    
def merge_headers(directory):
    import uuid
    from datetime import datetime

    forward = str(uuid.uuid4()).upper().replace('-', '_')
    
    lines = []
    lines.append('#pragma once')
    lines.append('#ifndef BIBIM_ALL_{0}_H__'.format(forward))
    lines.append('#define BIBIM_ALL_{0}_H__'.format(forward))
    lines.append('')
    lines.append('// Automatically generated in {0}'.format(datetime.now()))
    lines.append('')
    for item in os.listdir(directory):
        if file_ext(item) == 'h' and item != 'GLES2.h':
            lines.append('#include "{0}"'.format(item))
    lines.append('')
    lines.append('#endif')
    
    f = open(os.path.join(directory, 'All.h'), 'w')
    f.write('\n'.join(lines))
    f.close()


if __name__ == '__main__':
    print('publish libraries...')

    publish_library(ENVIRONMENT.VS2008, PLATFORM.WIN32, TARGET.DEBUG)
    publish_library(ENVIRONMENT.VS2008, PLATFORM.WIN32, TARGET.RELEASE)

    publish_library(ENVIRONMENT.VS2010, PLATFORM.WIN32,   TARGET.DEBUG)
    publish_library(ENVIRONMENT.VS2010, PLATFORM.WIN32,   TARGET.RELEASE)
    publish_library(ENVIRONMENT.VS2010, PLATFORM.ANDROID, TARGET.DEBUG)
    publish_library(ENVIRONMENT.VS2010, PLATFORM.ANDROID, TARGET.RELEASE)

    publish_library(ENVIRONMENT.VS2013, PLATFORM.WIN32,   TARGET.DEBUG)
    publish_library(ENVIRONMENT.VS2013, PLATFORM.WIN32,   TARGET.RELEASE)
    publish_library(ENVIRONMENT.VS2013, PLATFORM.ANDROID, TARGET.DEBUG)
    publish_library(ENVIRONMENT.VS2013, PLATFORM.ANDROID, TARGET.RELEASE)

    # publish_library(ENVIRONMENT.VS2010, PLATFORM.EMSCRIPTEN, TARGET.DEBUG)
    # publish_library(ENVIRONMENT.VS2010, PLATFORM.EMSCRIPTEN, TARGET.RELEASE)

    merge_sources('src')
    
    merge_headers('include/Bibim');