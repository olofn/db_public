import os
import time
import shutil
import zipfile

def recursive_zip(zipf, directory, folder = ""):
   for item in os.listdir(directory):
      if os.path.isfile(os.path.join(directory, item)):
         zipf.write(os.path.join(directory, item), folder + os.sep + item)
      elif os.path.isdir(os.path.join(directory, item)):
         recursive_zip(zipf, os.path.join(directory, item), folder + os.sep + item)

os.system("C:/Windows/Microsoft.NET/Framework/v3.5/MSBuild.exe db-speedhack11.sln /p:configuration=release /p:platform=Win32")
serialNumber = time.strftime("%Y-%m-%d_%H%M%S")
srcFolder = "db-speedhack11_"+serialNumber+"_src"
srcBuildFolder = "builds/"+srcFolder
binaryFolder = "db-speedhack11_"+serialNumber+"_bin"
binaryBuildFolder = "builds/"+binaryFolder

os.mkdir(srcBuildFolder)
os.mkdir(binaryBuildFolder)

shutil.copytree("data",srcBuildFolder+"/data", ignore=shutil.ignore_patterns('*.svn*'))
shutil.copytree("data",binaryBuildFolder+"/data", ignore=shutil.ignore_patterns('*.svn*'))
shutil.copytree("src",srcBuildFolder+"/src", ignore=shutil.ignore_patterns('*.svn*'))
shutil.copy("README.txt", srcBuildFolder)
shutil.copy("README.txt", binaryBuildFolder)
shutil.copy("COPYING.txt", srcBuildFolder)
shutil.copy("COPYING.txt", binaryBuildFolder)
shutil.copy("BSD-license.txt", srcBuildFolder)
shutil.copy("BSD-license.txt", binaryBuildFolder)
shutil.copy("Dumb-license.txt", srcBuildFolder)
shutil.copy("Dumb-license.txt", binaryBuildFolder)
shutil.copy("tmx-parser-license.txt", binaryBuildFolder)
shutil.copy("tmx-parser-license.txt", srcBuildFolder)
shutil.copy("Release/db-08_green_grappler.exe", binaryBuildFolder)
shutil.copy("allegro-4.4.2-mt.dll", binaryBuildFolder)

os.chdir("builds")
recursive_zip(zipfile.ZipFile(binaryFolder+".zip", 'w', zipfile.ZIP_DEFLATED), binaryFolder)
recursive_zip(zipfile.ZipFile(srcFolder+".zip", 'w', zipfile.ZIP_DEFLATED), srcFolder)
os.chdir("../")
