PROJECT_CEEDLING_ROOT = "vendor/ceedling"
load "#{PROJECT_CEEDLING_ROOT}/lib/ceedling.rb"

Ceedling.load_project

task :default => %w[ test:all release ]

desc "Program gpib2usb adapter using pickit3."
task :program => :release do
  hex_file = "build/release/#{RELEASE_BUILD_OUTPUT}.hex"
  cmd = "ipecmd.sh /P#{ENV['MCU']}  -TPPK3 /L /OL -F#{hex_file} -M"
  puts cmd
  sh cmd
end
