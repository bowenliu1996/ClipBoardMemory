; Inno Setup Script for packaging bin folder
[Setup]
AppId={{7A00ED0D-5B13-4C50-8DAE-775E96B9C25E}}
AppName=Clipboardmemory
AppVersion=1.0.0.1
AppPublisher="bowenliu1996"
DefaultDirName={pf}\Clipboardmemory
DefaultGroupName=bwWinTool
OutputDir=.
OutputBaseFilename=Clipboardmemory
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D3Dcompiler_47.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "QTClipboardmemory.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Pdf.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Svg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "opengl32sw.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "generic/qtuiotouchplugin.dll"; DestDir: "{app}\generic"; Flags: ignoreversion
Source: "iconengines/qsvgicon.dll"; DestDir: "{app}\iconengines"; Flags: ignoreversion
Source: "imageformats/qgif.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "imageformats/qicns.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "imageformats/qico.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "imageformats/qjpeg.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "imageformats/qpdf.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "imageformats/qsvg.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "imageformats/qtga.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "imageformats/qtiff.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "imageformats/qwbmp.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "imageformats/qwebp.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "networkinformation/qnetworklistmanager.dll"; DestDir: "{app}\networkinformation"; Flags: ignoreversion
Source: "platforms/qwindows.dll"; DestDir: "{app}\platforms"; Flags: ignoreversion
Source: "styles/qwindowsvistastyle.dll"; DestDir: "{app}\styles"; Flags: ignoreversion
Source: "tls/qcertonlybackend.dll"; DestDir: "{app}\tls"; Flags: ignoreversion
Source: "tls/qopensslbackend.dll"; DestDir: "{app}\tls"; Flags: ignoreversion
Source: "tls/qschannelbackend.dll"; DestDir: "{app}\tls"; Flags: ignoreversion
Source: "translations/qt_ar.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_bg.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_ca.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_cs.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_da.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_de.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_en.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_es.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_fa.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_fi.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_fr.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_gd.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_he.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_hr.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_hu.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_it.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_ja.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_ko.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_lv.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_nl.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_nn.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_pl.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_pt_BR.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_ru.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_sk.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_tr.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_uk.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_zh_CN.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "translations/qt_zh_TW.qm"; DestDir: "{app}\translations"; Flags: ignoreversion

[Icons]
Name: "{group}\Clipboardmemory"; Filename: "{app}\QTClipboardmemory.exe"
Name: "{commondesktop}\Clipboardmemory"; Filename: "{app}\QTClipboardmemory.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\QTClipboardmemory.exe"; Description: "{cm:LaunchProgram,Clipboardmemory}"; Flags: nowait postinstall skipifsilent
