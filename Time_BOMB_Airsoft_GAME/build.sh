#!/bin/bash
rm -rf result
mkdir -p result
echo "PUB_HOSTED_URL: "$PUB_HOSTED_URL
echo "FLUTTER_STORAGE_BASE_URL: "$FLUTTER_STORAGE_BASE_URL
echo $PWD
echo "###################################################################################################################"
echo "Flutter Build start ..."
flutter --version

# 解除 Flutter 构建锁
lockFile="$FLUTTER_ROOT/bin/cache/lockfile"
#lockFile="/Users/elvissu/Documents/日常学习/flutter/bin/cache/lockfile"
if [[ -a "$lockFile" ]]; then
echo "存在lockfile文件";
rm -f "$lockFile"
fi

pubCache="/Users/bkdevops/.pub-cache"
rm -rf "$pubCache"

echo "prepare end.........."

# 生成版本号
appVersion=$MajorVersion"."$MinorVersion"."$FixVersion
echo "App Version: "$appVersion

appBuildNumber=$BuildNo
echo "App Build Number: "$appBuildNumber

echo "###################################################################################################################"
echo "Start build iOS App"

function buildAppleTarget() {
    
    _version=$1
    _buildNumber=$2
    _buildTarget=$3
    _targetFile=$4

    # 设置版本号
    echo "Start Version Settting"
    app_info_plist_path="ios/Runner/Info.plist"
    /usr/libexec/PlistBuddy -c "Set :CFBundleVersion ${appBuildNumber}" ${app_info_plist_path}
    /usr/libexec/PlistBuddy -c "Set :CFBundleShortVersionString ${appVersion}" ${app_info_plist_path}
    echo "End Version Settting"

    # 开始构建
    flutter build ios --build-name=$_version --build-number=$_buildNumber --release $_targetFile

    # 生成 .ipa 文件
    rm -rf build/ios/iphoneos/ipa/
    mkdir -p build/ios/iphoneos/ipa/Payload
    cp -R build/ios/iphoneos/Runner.app build/ios/iphoneos/ipa/Payload/
    cd build/ios/iphoneos/ipa
    zip -r app-release.ipa Payload

    _appName="app-release-codesign"

    cd ../../../../
    echo $PWD

    #if [[ $LANDUN ]]
    #then
    # 拷贝到输出结果目录
    #cp build/ios/iphoneos/ipa/app-release.ipa result/k12hd-$_buildTarget-$_version"."$_buildNumber".ipa"
    #cp build/ios/iphoneos/ipa/"$_appName".ipa result/aieducation-$_buildTarget-$_version"."$_buildNumber".sign.ipa"
    #else
    # 拷贝到输出结果目录
    #cp build/ios/iphoneos/ipa/app-release.ipa $WORKSPACE/result/k12hd-$_buildTarget-$_version"."$_buildNumber".ipa"
    #cp build/ios/iphoneos/ipa/"$_appName".ipa $WORKSPACE/result/k12hd-$_buildTarget-$_version"."$_buildNumber".sign.ipa"
    #fi
    cp build/ios/iphoneos/ipa/app-release.ipa output/caige-$_version.$_buildNumber-release.ipa
    
    echo "copy release ipa done"
}

setEnv "commit" "$(git log -1 --oneline)"
setEnv "author" "$(git log -1 --pretty=%aN)"
# setEnv "qua" ${QUA}

function writeConfig() {
    echo "{\"isProduction\":${isProduction}, \"QUAVer\": \"${QUAVer}\", \"QUAPlatform_BusinessId\": \"${QUAPlatform_BusinessId}\", \"QUAAppVersion\": \"${appVersion}\", \"QUABuildNo\": \"${BuildNo}\", \"QUAChannel\": \"${QUAChannel}\"" > config.json
}

writeConfig

#----------------------
# 功能：修改编译参数
# ----------------------
function writeBuildDefine() {
    echo "
#ifndef BuildDefine_h
#define BuildDefine_h

//是否为正式版
#define isProduction ${isProduction}

//QUA版本号
#define QUAVer @\"${QUAVer}\"

//平台信息+业务
#define QUAPlatform_BusinessId  @\"${QUAPlatform_BusinessId}\"

//渠道号
#define QUAChannel @\"${QUAChannel}\"

#endif /* BuildDefine_h */
" > ./ios/Runner/BuildDefine.h
}

writeBuildDefine

buildAppleTarget $appVersion $appBuildNumber $buildTarget $targetFile

#if [[ $buildTarget == DailyBuild ]]; then
#    # 在iPhone版的RDM中只能生成iPad的测试包，发布包必须在iPad的RDM中生成，为了避免混乱，只在测试包时生成iPad包。
#    buildAppleTarget $appVersion $appBuildNumber iPad "--target=lib/ipad.dart"
#fi

echo "###################################################################################################################"
echo "Build Finish"
echo "###################################################################################################################"
exit 0
