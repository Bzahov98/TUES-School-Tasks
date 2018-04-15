Dir.glob(ARGV[0]+"*").each do |file|
    result = file.split("/").last.split("_")
    p "#{result[0]},#{result[1]},#{result[2]},#{result[3].split(".").first}"
    p `ruby #{file} 1 3 2`
end


fileObj = File.new($fileName, "r")
while (line = fileObj.gets)
  puts(line)
end
fileObj.close
