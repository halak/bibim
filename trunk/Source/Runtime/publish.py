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

PRODUCT_DIR = '../../Product/'
INCLUDE_DIR = os.path.join(PRODUCT_DIR, 'Include')
LIBRARY_DIR = os.path.join(PRODUCT_DIR, 'Lib')

PRODUCT_ABS_DIR = '$(BIBIM_DIR)Product/'
INCLUDE_ABS_DIR = os.path.join(PRODUCT_ABS_DIR, 'Include')
LIBRARY_ABS_DIR = os.path.join(PRODUCT_ABS_DIR, 'Lib')


def file_ext(filename):
    return os.path.splitext(filename)[1][1:]


def copy_headers(module_name):
    from shutil import copy2, copystat
    src = './Cplusplus/{0}/Bibim/'.format(module_name)
    dst = os.path.join(INCLUDE_DIR, 'Bibim')
    names = os.listdir(src)

    errors = []
    for name in names:
        if (file_ext(name) not in ('h',)):
            continue

        srcname = os.path.join(src, name)
        dstname = os.path.join(dst, name)
        try:
            copy2(srcname, dstname)
        except (IOError, os.error) as why:
            errors.append((srcname, dstname, str(why)))
        except Error as err:
            errors.extend(err.args[0])
    try:
        copystat(src, dst)
    except WindowsError:
        pass
    except OSError as why:
        errors.extend((src, dst, str(why)))
    if errors:
        raise Error(errors)
        

def copy_references_header(src):
    from shutil import copy2
    copy2(src, INCLUDE_DIR)


class PLATFORM:
    WIN32 = 1
    ANDROID = 2
    IOS = 3

    @staticmethod
    def to_string(code):
        if (code == PLATFORM.WIN32):
            return 'Win32'
        elif (code == PLATFORM.ANDROID):
            return 'Android'
        elif (code == PLATFORM.IOS):
            return 'iOS'
        else:
            return None

    
class TARGET:
    DEBUG = 1
    RELEASE = 2
    
    @staticmethod
    def to_string(code):
        if (code == TARGET.DEBUG):
            return 'Debug'
        elif (code == TARGET.RELEASE):
            return 'Release'
        else:
            return None
    
    
class ENVIRONMENT:
    VC9 = 1
    VC10 = 2

    @staticmethod
    def to_string(code):
        if (code == ENVIRONMENT.VC9):
            return 'VC9'
        elif (code == ENVIRONMENT.VC10):
            return 'VC10'
        else:
            return None
    
    
def get_include_directories(platform, target, environment):
    l = []
    l += [INCLUDE_ABS_DIR]

    if (platform == PLATFORM.WIN32):
        l += ['$(DXSDK_DIR)Include']
    
    return l
    
    
def get_library_directories(platform, target, environment):
    l = []
    if (platform == PLATFORM.WIN32):
        l += ['$(DXSDK_DIR)Lib/x86']
    
    return l    

    
def get_dependencies(platform, target, environment):
    l = []
    win32 = platform == PLATFORM.WIN32
    android = platform == PLATFORM.ANDROID
    ios = platform == PLATFORM.IOS
    debug = target == TARGET.DEBUG
    release = target == TARGET.RELEASE
    vc9 = environment == ENVIRONMENT.VC9 
    vc10 = environment == ENVIRONMENT.VC10

    # BIBIM
    if (win32):
        l += ['Bibim.lib']
    elif (android):
        l += ['Bibim.a']
    
    # Platform
    if (win32):
        l += ['winmm.lib']
        l += ['ws2_32.lib']
    
    # DirectX9
    if (win32):
        l += ['d3d9.lib']
        if (debug):
            l += ['d3dx9d.lib']
        elif (release):
            l += ['d3dx9.lib']
     
    # ZLib & PNG & JPG & FreeType & Lua & SPARK & Curl
    if (win32):
        if (debug):
            if (vc9):
                l += ['Cplusplus/References/zlib-1.2.8/lib/Win32/Debug/vs2008/zlib.lib']
                l += ['Cplusplus/References/libpng-1.6.3/lib/Win32/Debug/vs2008/libpng.lib']
                l += ['Cplusplus/References/jpeg-9/lib/Win32/Debug/vs2008/libjpeg.lib']
                l += ['Cplusplus/References/freetype-2.5.0.1/custom/lib/Win32/Debug/vs2008/freetype.lib']
                l += ['Cplusplus/References/lua-5.2.2/lib/Win32/Debug/vs2008/lua.lib']
                l += ['Cplusplus/References/SPARK-1.5.5/lib/vc2008/static/SPARK_debug.lib']
                l += ['Cplusplus/References/curl-7.29.0/build/Win32/LIB Debug/vs2008/libcurl.lib']
            elif (vc10):
                l += ['Cplusplus/References/zlib-1.2.8/lib/Win32/Debug/vs2010/zlib.lib']
                l += ['Cplusplus/References/libpng-1.6.3/lib/Win32/Debug/vs2010/libpng.lib']
                l += ['Cplusplus/References/jpeg-9/lib/Win32/Debug/vs2010/libjpeg.lib']
                l += ['Cplusplus/References/freetype-2.5.0.1/custom/lib/Win32/Debug/vs2010/freetype.lib']
                l += ['Cplusplus/References/lua-5.2.2/lib/Win32/Debug/vs2010/lua.lib']
                l += ['Cplusplus/References/SPARK-1.5.5/lib/vc2010/static/SPARK_debug.lib']
                l += ['Cplusplus/References/curl-7.29.0/build/Win32/LIB Debug/vs2010/libcurl.lib']
        elif (release):
            if (vc9):
                l += ['Cplusplus/References/zlib-1.2.8/lib/Win32/Release/vs2008/zlib.lib']
                l += ['Cplusplus/References/libpng-1.6.3/lib/Win32/Release/vs2008/libpng.lib']
                l += ['Cplusplus/References/jpeg-9/lib/Win32/Release/vs2008/libjpeg.lib']
                l += ['Cplusplus/References/freetype-2.5.0.1/custom/lib/Win32/Release/vs2008/freetype.lib']
                l += ['Cplusplus/References/lua-5.2.2/lib/Win32/Release/vs2008/lua.lib']
                l += ['Cplusplus/References/SPARK-1.5.5/lib/vc2008/static/SPARK.lib']
                l += ['Cplusplus/References/curl-7.29.0/build/Win32/LIB Release/vs2008/libcurl.lib']
            elif (vc10):
                l += ['Cplusplus/References/zlib-1.2.8/lib/Win32/Release/vs2010/zlib.lib']
                l += ['Cplusplus/References/libpng-1.6.3/lib/Win32/Release/vs2010/libpng.lib']
                l += ['Cplusplus/References/jpeg-9/lib/Win32/Release/vs2010/libjpeg.lib']
                l += ['Cplusplus/References/freetype-2.5.0.1/custom/lib/Win32/Release/vs2010/freetype.lib']
                l += ['Cplusplus/References/lua-5.2.2/lib/Win32/Release/vs2010/lua.lib']
                l += ['Cplusplus/References/SPARK-1.5.5/lib/vc2010/static/SPARK.lib']
                l += ['Cplusplus/References/curl-7.29.0/build/Win32/LIB Release/vs2010/libcurl.lib']
    elif (android):
        if (debug):
            l += ['Cplusplus/References/libpng-1.6.3/lib/Android/Debug/vs2010/libpng.a']
            l += ['Cplusplus/References/zlib-1.2.8/lib/Android/Debug/vs2010/zlib.a']
            l += ['Cplusplus/References/jpeg-9/lib/Android/Debug/vs2010/libjpeg.a']
            l += ['Cplusplus/References/freetype-2.5.0.1/custom/lib/Android/Debug/vs2010/freetype.a']
            l += ['Cplusplus/References/lua-5.2.2/lib/Android/Debug/vs2010/lua.a']
            l += ['Cplusplus/References/SPARK-1.5.5/lib/vc2010/static/SPARK_android_debug.a']
            l += ['Cplusplus/References/curl-7.29.0/build/Android/LIB Debug/vs2010/libcurl.a']
        elif (release):
            l += ['Cplusplus/References/libpng-1.6.3/lib/Android/Release/vs2010/libpng.a']
            l += ['Cplusplus/References/zlib-1.2.8/lib/Android/Release/vs2010/zlib.a']
            l += ['Cplusplus/References/jpeg-9/lib/Android/Release/vs2010/libjpeg.a']
            l += ['Cplusplus/References/freetype-2.5.0.1/custom/lib/Android/Release/vs2010/freetype.a']
            l += ['Cplusplus/References/lua-5.2.2/lib/Android/Release/vs2010/lua.a']
            l += ['Cplusplus/References/SPARK-1.5.5/lib/vc2010/static/SPARK_android.a']
            l += ['Cplusplus/References/curl-7.29.0/build/Android/LIB Release/vs2010/libcurl.a']
    
    # irrKlang
    if (win32):
        l += ['Cplusplus/References/irrKlang-1.4.0/lib/Win32-visualStudio/irrKlang.lib']
        
    # OpenAL
    if (win32):
        l += ['Cplusplus/References/OpenAL/PC/libs/Win32/OpenAL32.lib']
    elif (android):
        l += ['Cplusplus/References/OpenAL/Android/libs/armeabi/libopenal.so']
        l += ['Cplusplus/References/OpenAL/Android/libs/armeabi/libopenalwrapper.so']
        
    # MPQ
    if (win32):
        if (vc9):
            if (debug):
                l += ['Cplusplus/References/StormLib/lib/Win32/Debug/vs2008/StormLibDAD.lib']
            elif (release):
                l += ['Cplusplus/References/StormLib/lib/Win32/Release/vs2008/StormLibRAD.lib']
        elif (vc10):
            if (debug):
                l += ['Cplusplus/References/StormLib/lib/Win32/Debug/vs2010/StormLibDAD.lib']
            elif (release):
                l += ['Cplusplus/References/StormLib/lib/Win32/Release/vs2010/StormLibRAD.lib']

    return l
        

def save_xml(filename, element):
    import xml.etree.ElementTree as ET
    xml_text = ET.tostring(element, 'utf-8')
    
    f = open(filename, 'w')
    f.write('<?xml version="1.0" encoding="utf-8"?>\n')
    f.write(xml_text)
    f.close()
    
    
def make_bibim_name(platform, target, environment):    
    platform = PLATFORM.to_string(platform)
    target = TARGET.to_string(target)
    environment = ENVIRONMENT.to_string(environment)
    
    components = ['Bibim']
    if (platform):
        components.append(platform)
    if (target):
        components.append(target)
    if (environment):
        components.append(environment)

    return '.'.join(components)


def make_visual_studio_property_sheet_8(name,
                                        include_directories,
                                        library_directories,
                                        depdendencies):
                                        
    import xml.etree.ElementTree as ET
    root = ET.Element('VisualStudioPropertySheet', {
        'ProjectType': 'Visual C++',
        'Version': '8.00',
        'Name': name,
    })
    
    root.append(ET.Element('Tool', {
        'Name': 'VCCLCompilerTool',
        'AdditionalIncludeDirectories': include_directories.replace('/', '\\'),
        'PreprocessorDefinitions': 'CURL_STATICLIB',
        'WarningLevel': '4',
    }))
    root.append(ET.Element('Tool', {
        'Name': 'VCLinkerTool',
        'AdditionalDependencies': depdendencies.replace('/', '\\').replace(';', ' '),
        'AdditionalLibraryDirectories': library_directories.replace('/', '\\'),
    }))
    
    return root
    
    
def make_visual_studio_property_sheet_10(name,
                                         include_directories,
                                         library_directories,
                                         depdendencies,
                                         platform=None):
    
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
    if (platform and platform == PLATFORM.ANDROID):
        link.append(ETElementWithText(
            'AdditionalOptions',
            '-lGLESv2 -landroid %(AdditionalOptions)'
        ))
    item_definition_group.append(link)
    root.append(item_definition_group)
    
    return root
    
    
def publish_library(platform, target, environment):
    name = make_bibim_name(platform, target, environment)
    library_relative_directory = name.strip('Bibim.').replace('.', '/')
    main_library_directory = os.path.join(LIBRARY_ABS_DIR, library_relative_directory)
    
    # 추가 포함 디렉터리와 라이브러리 디렉터리를 구합니다.
    include_directories = get_include_directories(platform, target, environment)
    include_directory = ';'.join(map(lambda o: '"{0}"'.format(o), include_directories))
    library_directories = get_library_directories(platform, target, environment)
    library_directories += [main_library_directory]
    library_directory = ';'.join(map(lambda o: '"{0}"'.format(o), library_directories))
        
    # 의존 라이브러리들 목록을 구합니다.
    dependencies = get_dependencies(platform, target, environment)
    if (platform == PLATFORM.ANDROID):
        dependency_filenames = ';'.join(map(
            lambda o: os.path.join(main_library_directory, os.path.basename(o)),
            dependencies
        ))
    else:
        dependency_filenames = ';'.join(map(
            lambda o: os.path.basename(o),
            dependencies
        ))
    
    # 환경에 맞는 프로퍼티 시트를 생성해서 저장합니다.
    if (environment == ENVIRONMENT.VC9):
        element = make_visual_studio_property_sheet_8(name,
                                                      include_directory,
                                                      library_directory,
                                                      dependency_filenames)
        save_xml('{0}{1}.vsprops'.format(PRODUCT_DIR, name), element)
    elif (environment == ENVIRONMENT.VC10):
        element = make_visual_studio_property_sheet_10(name,
                                                       include_directory,
                                                       library_directory,
                                                       dependency_filenames,
                                                       platform)
        save_xml('{0}{1}.props'.format(PRODUCT_DIR, name), element)
 
    # 의존 라이브러리들을 Product 폴더로 복사합니다.
    library_directory = os.path.join(LIBRARY_DIR, library_relative_directory)
    from shutil import copy2
    for item in dependencies:
        if (item.startswith('Cplusplus/References')):  # 로컬에 있는 라이브러리만 복사합니다.
            copy2(item, library_directory)

            
if (__name__ == '__main__'):
    import sys
    header_only = (len(sys.argv) >= 2 and sys.argv[1] == 'header-only')
    
    print('publish headers...')

    for module in MODULES:
        copy_headers(module)
    copy_references_header('Cplusplus/References/lua-5.2.2/src/lua.h')
    copy_references_header('Cplusplus/References/lua-5.2.2/src/lauxlib.h')
    copy_references_header('Cplusplus/References/lua-5.2.2/src/luaconf.h')
    copy_references_header('Cplusplus/References/lua-5.2.2/src/lualib.h')
    copy_references_header('Cplusplus/References/lua_tinker/lua_tinker.h')
    
    copy_references_header('ObjectiveC/Bibim/Bibim/BibimAppDelegate.h')
    copy_references_header('ObjectiveC/Bibim/Bibim/BibimViewController.h')
    
    if (not header_only):
        print('publish libraries...')
        
        publish_library(PLATFORM.WIN32, TARGET.DEBUG,   ENVIRONMENT.VC9)
        publish_library(PLATFORM.WIN32, TARGET.RELEASE, ENVIRONMENT.VC9)

        publish_library(PLATFORM.WIN32,   TARGET.DEBUG,   ENVIRONMENT.VC10)
        publish_library(PLATFORM.WIN32,   TARGET.RELEASE, ENVIRONMENT.VC10)
        publish_library(PLATFORM.ANDROID, TARGET.DEBUG,   ENVIRONMENT.VC10)
        publish_library(PLATFORM.ANDROID, TARGET.RELEASE, ENVIRONMENT.VC10)