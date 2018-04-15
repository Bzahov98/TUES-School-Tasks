#file=File.open(ARGV[0], 'r')

file = "FirstName3_LastName3Invalid.rb"
list = Hash.new

#marks = file.gsub(/\w/,'').split
i=0
file.each_line do |line,i|
	words = line.downcase.gsub(//,i).each do |word|
		if list.has_key?(word)
     			list[word] = list[word] + 1
    		  else
			list[word] = 1
	
		end
	end
end

list.sort{ |a,b| a[1] <=> b[1] }.each do |element| 
	puts "#{element[0]},#{element[1]}"
end

marks_str=marks.join('').length

if (marks!=0)
     print "\"marks\",#{marks_str}\n"
end
