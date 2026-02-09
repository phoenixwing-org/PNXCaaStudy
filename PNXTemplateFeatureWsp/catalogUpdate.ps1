# 修正版本

$catalogTitle="PNXTemplateFeature"
$Version = $env:CAA_MK_VERSION
$destinationDir=".\win_b64\resources\graphic\"

Write-Host "### Create or upadate $catalogTitle catalog for version $Version" -ForegroundColor Yellow
cd $PSScriptRoot

# 临时设置PATH
$env:PATH = "C:\DS\B$Version\win_b64\code\bin;$PSScriptRoot\win_b64\code\bin;$env:PATH"

Write-Host "- ${catalogTitle}Catalog.\${catalogTitle}Frm\CNext\resources\graphic" -ForegroundColor Yellow
# 执行程序 - 正确拼接变量
& "${catalogTitle}Catalog" ".\${catalogTitle}Frm\CNext\resources\graphic"

# 复制文件
Copy-Item ".\${catalogTitle}Frm\CNext\resources\graphic\*.CATFct" $destinationDir -Force

Write-Host "- Files copied successfully to $destinationDir" -ForegroundColor Green