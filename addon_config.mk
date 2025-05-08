# All variables and this file are optional, if they are not present the PG and the
# makefiles will try to parse the correct values from the file system.
#
# Variables that specify exclusions can use % as a wildcard to specify that anything in
# that position will match. A partial path can also be specified to, for example, exclude
# a whole folder from the parsed paths from the file system
#
# Variables can be specified using = or +=
# = will clear the contents of that variable both specified from the file or the ones parsed
# from the file system
# += will add the values to the previous ones in the file or the ones parsed from the file 
# system
# 
# The PG can be used to detect errors in this file, just create a new project with this addon 
# and the PG will write to the console the kind of error and in which line it is

meta:
	ADDON_NAME = ofxAntilatency
	ADDON_DESCRIPTION = Wrapper for Antilatency SDK
	ADDON_AUTHOR = Hiroyuki Hori
	ADDON_TAGS = "Antilatency"
	ADDON_URL = https://github.com/P-A-N/ofxAntilatency

common:
	# dependencies with other addons, a list of them separated by spaces 
	# or use += in several lines
	#ADDON_DEPENDENCIES =
	
	# include search paths, this will be usually parsed from the file system
	# but if the addon or addon libraries need special search paths they can be
	# specified here separated by spaces or one per line using +=
	# ADDON_INCLUDES =
	# ADDON_INCLUDES_EXCLUDE = libs
	# ADDON_INCLUDES_EXCLUDE += libs/Api
	# ADDON_INCLUDES_EXCLUDE += libs/Api/%
	
linux64:
	ADDON_LIBS = libs/Bin/Linux/aarch64_linux_gnu/libAntilatencyAltEnvironmentAdditionalMarkers.so
	ADDON_LIBS += libs/Bin/Linux/aarch64_linux_gnu/libAntilatencyAltEnvironmentArbitrary2D.so
	ADDON_LIBS += libs/Bin/Linux/aarch64_linux_gnu/libAntilatencyAltEnvironmentHorizontalGrid.so
	ADDON_LIBS += libs/Bin/Linux/aarch64_linux_gnu/libAntilatencyAltEnvironmentPillars.so
	ADDON_LIBS += libs/Bin/Linux/aarch64_linux_gnu/libAntilatencyAltEnvironmentRectangle.so
	ADDON_LIBS += libs/Bin/Linux/aarch64_linux_gnu/libAntilatencyAltEnvironmentSelector.so
	ADDON_LIBS += libs/Bin/Linux/aarch64_linux_gnu/libAntilatencyAltEnvironmentSides.so
	ADDON_LIBS += libs/Bin/Linux/aarch64_linux_gnu/libAntilatencyAltTracking.so
	ADDON_LIBS += libs/Bin/Linux/aarch64_linux_gnu/libAntilatencyBracer.so
	ADDON_LIBS += libs/Bin/Linux/aarch64_linux_gnu/libAntilatencyDeviceNetwork.so
	ADDON_LIBS += libs/Bin/Linux/aarch64_linux_gnu/libAntilatencyHardwareExtensionInterface.so
	ADDON_LIBS += libs/Bin/Linux/aarch64_linux_gnu/libAntilatencyPhysicalConfigurableEnvironment.so
	ADDON_LIBS += libs/Bin/Linux/aarch64_linux_gnu/libAntilatencyRadioMetrics.so
	ADDON_LIBS += libs/Bin/Linux/aarch64_linux_gnu/libAntilatencyStorageClient.so
	ADDON_LIBS += libs/Bin/Linux/aarch64_linux_gnu/libAntilatencyTrackingAlignment.so
	# any special flag that should be passed to the compiler when using this
	# addon
	# ADDON_CFLAGS =
	
	# any special flag that should be passed to the linker when using this
	# addon, also used for system libraries with -lname
	# ADDON_LDFLAGS =
	
	# linux only, any library that should be included in the project using
	# pkg-config
	
	# osx/iOS only, any framework that should be included in the project
	# ADDON_FRAMEWORKS =
	
	# source files, these will be usually parsed from the file system looking
	# in the src folders in libs and the root of the addon. if your addon needs
	# to include files in different places or a different set of files per platform
	# they can be specified here
	# ADDON_SOURCES =
	
	# some addons need resources to be copied to the bin/data folder of the project
	# specify here any files that need to be copied, you can use wildcards like * and ?
	# ADDON_DATA = 
	
	# when parsing the file system looking for libraries exclude this for all or
	# a specific platform
	#ADDON_LIBS_EXCLUDE =
