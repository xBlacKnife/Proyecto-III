rem Ramón Arjona Quiñones, 2019
rem Script de compilación para ProyectoIII que crea la solución de VS con CMake, compila Ogre y mueve los dll necesarios para la ejecución del mismo
@echo on

mkdir tmp
Xcopy exes\*.cfg tmp
del /q exes\*

Xcopy Dependencias\ogre-1.11.5\Build\bin\debug\OgreMain_d.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\release\OgreMain.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\debug\RenderSystem_GL_d.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\release\RenderSystem_GL.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\release\zlib.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\debug\Codec_STBI_d.dll exes
Xcopy Dependencias\ogre-1.11.5\Build\bin\release\Codec_STBI.dll exes

Xcopy tmp\* exes

del /q tmp
rmdir tmp


