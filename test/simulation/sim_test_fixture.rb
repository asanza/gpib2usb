OUT_FILE = "test/simulation/out.txt"
File.delete OUT_FILE if File.exists? OUT_FILE
IO.popen("simulavr -d at90can128 -f build/test/TestBuild.elf -W 0x20,test/simulation/simlog.txt -R 0x22,- -T UnityEnd")
sleep 10
if File.exists? OUT_FILE
    file_contents = File.read OUT_FILE
    file_contents.gsub!("\r\n","\n")
    print file_contents
    #puts file_contents.gsub("\n"){""}
end
