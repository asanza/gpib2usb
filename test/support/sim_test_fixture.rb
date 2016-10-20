require 'rbconfig'
is_windows = (RbConfig::CONFIG['host_os'] =~ /mswin|mingw|cygwin/)
OUT_FILE = "./test/support/out.txt"
File.delete OUT_FILE if File.exists? OUT_FILE
if is_windows
	var = IO.popen("mdb.bat ./test/support/sim_instructions.txt > ./test/support/simlog.txt")
else
	var = IO.popen("/opt/microchip/mplabx/v3.05/mplab_ide/bin/mdb.sh ./test/support/sim_instructions.txt > ./test/support/simlog.txt")
end
Process.wait
if File.exists? OUT_FILE
    file_contents = File.read OUT_FILE
    file_contents.gsub!("\r\n","\n")
    print file_contents
    #puts file_contents.gsub("\n"){""}
end
