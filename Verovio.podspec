Pod::Spec.new do |s|
  s.name           = 'Verovio'
  s.version        = '2.1.0'
  s.license        = { :type => 'LGPL' }
  s.homepage       = 'https://www.verovio.org/index.xhtml'
  s.authors        = { 'Contributors List' => 'https://github.com/rism-ch/verovio/graphs/contributors' }
  s.summary        = 'Verovio'
  s.source         = { :git => 'https://github.com/rism-ch/verovio.git', :tag => 'version-' + s.version.to_s }
  s.swift_versions = ['5.1']
  s.source_files        = 'src/**/*.{h,cpp,cc}',
                          'include/{hum,json,midi,pugi,utf8,vrv}/*.{h,hpp}',
                          'libmei/{attclasses,attconverter,atts_analytical,atts_cmn,atts_cmnornaments}.{h,cpp}',
                          'libmei/{atts_critapp,atts_externalsymbols,atts_facsimile,atts_gestural,atts_mei}.{h,cpp}', 
                          'libmei/{atts_mensural,atts_midi,atts_neumes,atts_pagebased,atts_shared}.{h,cpp}',
                          'libmei/{atts_visual,atttypes}.{h,cpp}'
  s.public_header_files = 'src/**/*.{h}',
                          'include/{hum,json,midi,pugi,utf8,vrv}/*.{h,hpp}',
                          'libmei/{attclasses,attconverter,atts_analytical,atts_cmn,atts_cmnornaments}.{h}',
                          'libmei/{atts_critapp,atts_externalsymbols,atts_facsimile,atts_gestural,atts_mei}.{h}', 
                          'libmei/{atts_mensural,atts_midi,atts_neumes,atts_pagebased,atts_shared}.{h}',
                          'libmei/{atts_visual,atttypes}.{h}'
  s.platform       = :ios, '12.0'
  s.resources      = 'data'
  s.xcconfig = {
      "CLANG_CXX_LANGUAGE_STANDARD" => "gnu++14",
      "CLANG_CXX_LIBRARY" => "libc++",
      "GCC_C_LANGUAGE_STANDARD" => "gnu11",
      "GCC_DYNAMIC_NO_PIC" => "NO",
      "GCC_NO_COMMON_BLOCKS" => "YES",
      "GCC_SYMBOLS_PRIVATE_EXTERN" => "NO",
      "CLANG_ENABLE_OBJC_ARC" => "YES",
      "CLANG_ENABLE_OBJC_WEAK" => "YES",
      "ENABLE_STRICT_OBJC_MSGSEND" => "YES",
      "MTL_FAST_MATH" => "YES",
      "SUPPORTS_UIKITFORMAC" => "NO",
      "MTL_ENABLE_DEBUG_INFO" => "NO"
    }
  s.info_plist = {
    'CFBundleIdentifier' => 'com.rism.VerovioFramework'
  }
end