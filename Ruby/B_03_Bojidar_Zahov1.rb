word_hash = Hash.new

file = File.new(ARGV[0], "r")

file.each do |l|
	word = file.downcase.split(" ")
	puts word.each
	
end
