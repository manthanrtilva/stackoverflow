require 'benchmark'

def sort1 (arr)
	int_arr = arr.select {|x| x.is_a?(Integer)}.sort
	str_arr = arr.select {|x| x.is_a?(String)}.sort
	return int_arr + str_arr;
end

def sort2(arr)
	return arr.partition { |e| e.is_a?(Integer) }.flat_map(&:sort);
end

def sort3(arr)
	return arr.sort_by { |e| [e.is_a?(Integer) ? 0 : 1, e] }
end

def sort4(arr)
	return arr.sort_by(&:ord)
end

def quick_sort(list)
  # unless list.empty?
  	return list.sort()
	  # groups = list.group_by { |n| n <=> list.first }
	  # return quick_sort(groups[-1] || []).push(*(groups[0]  || [])).push(*quick_sort(groups[1]  || []))
  # end
  # return []
end


def sort5(arr)
	# array = 
	return arr.partition { |e| e.is_a?(Integer) }.flat_map { |e| e.sort!() };
	# return quick_sort(array[0]) + quick_sort(array[1]);
end


arr = [4,2,'b',5,'c','a',7]

# print(arr,"\n")
# print(arr.partition { |e| e.is_a?(Integer) },"\n")
# print(arr,"\n")
# exit
# puts(arr.map!(&:ord))
ret = sort5(arr)
# print(ret,"\n")
raise "#{__FILE__}:#{__LINE__}:#{ret[0]} != 2" unless ret[0] == 2
raise "#{__FILE__}:#{__LINE__}:#{ret[1]} != 4" unless ret[1] == 4
raise "#{__FILE__}:#{__LINE__}:#{ret[2]} != 5" unless ret[2] == 5
raise "#{__FILE__}:#{__LINE__}:#{ret[3]} != 7" unless ret[3] == 7
raise "#{__FILE__}:#{__LINE__}:#{ret[4]} != 'a'" unless ret[4] == 'a'
raise "#{__FILE__}:#{__LINE__}:#{ret[5]} != 'b'" unless ret[5] == 'b'
raise "#{__FILE__}:#{__LINE__}:#{ret[6]} != 'c'" unless ret[6] == 'c'

# exit
# exit

ret = sort1(arr)
raise "#{__FILE__}:#{__LINE__}:#{ret[0]} != 2" unless ret[0] == 2
raise "#{__FILE__}:#{__LINE__}:#{ret[1]} != 4" unless ret[1] == 4
raise "#{__FILE__}:#{__LINE__}:#{ret[2]} != 5" unless ret[2] == 5
raise "#{__FILE__}:#{__LINE__}:#{ret[3]} != 7" unless ret[3] == 7
raise "#{__FILE__}:#{__LINE__}:#{ret[4]} != 'a'" unless ret[4] == 'a'
raise "#{__FILE__}:#{__LINE__}:#{ret[5]} != 'b'" unless ret[5] == 'b'
raise "#{__FILE__}:#{__LINE__}:#{ret[6]} != 'c'" unless ret[6] == 'c'

ret = sort2(arr)
raise "#{__FILE__}:#{__LINE__}:#{ret[0]} != 2" unless ret[0] == 2
raise "#{__FILE__}:#{__LINE__}:#{ret[1]} != 4" unless ret[1] == 4
raise "#{__FILE__}:#{__LINE__}:#{ret[2]} != 5" unless ret[2] == 5
raise "#{__FILE__}:#{__LINE__}:#{ret[3]} != 7" unless ret[3] == 7
raise "#{__FILE__}:#{__LINE__}:#{ret[4]} != 'a'" unless ret[4] == 'a'
raise "#{__FILE__}:#{__LINE__}:#{ret[5]} != 'b'" unless ret[5] == 'b'
raise "#{__FILE__}:#{__LINE__}:#{ret[6]} != 'c'" unless ret[6] == 'c'

ret = sort3(arr)
raise "#{__FILE__}:#{__LINE__}:#{ret[0]} != 2" unless ret[0] == 2
raise "#{__FILE__}:#{__LINE__}:#{ret[1]} != 4" unless ret[1] == 4
raise "#{__FILE__}:#{__LINE__}:#{ret[2]} != 5" unless ret[2] == 5
raise "#{__FILE__}:#{__LINE__}:#{ret[3]} != 7" unless ret[3] == 7
raise "#{__FILE__}:#{__LINE__}:#{ret[4]} != 'a'" unless ret[4] == 'a'
raise "#{__FILE__}:#{__LINE__}:#{ret[5]} != 'b'" unless ret[5] == 'b'
raise "#{__FILE__}:#{__LINE__}:#{ret[6]} != 'c'" unless ret[6] == 'c'

ret = sort4(arr)
raise "#{__FILE__}:#{__LINE__}:#{ret[0]} != 2" unless ret[0] == 2
raise "#{__FILE__}:#{__LINE__}:#{ret[1]} != 4" unless ret[1] == 4
raise "#{__FILE__}:#{__LINE__}:#{ret[2]} != 5" unless ret[2] == 5
raise "#{__FILE__}:#{__LINE__}:#{ret[3]} != 7" unless ret[3] == 7
raise "#{__FILE__}:#{__LINE__}:#{ret[4]} != 'a'" unless ret[4] == 'a'
raise "#{__FILE__}:#{__LINE__}:#{ret[5]} != 'b'" unless ret[5] == 'b'
raise "#{__FILE__}:#{__LINE__}:#{ret[6]} != 'c'" unless ret[6] == 'c'

n = 100000
Benchmark.bm do |x|
  x.report("sort1") { n.times do   ; ret = sort1(arr); end }
  x.report("sort2") { n.times do   ; ret = sort2(arr); end }
  x.report("sort3") { n.times do   ; ret = sort3(arr); end }
  x.report("sort4") { n.times do   ; ret = sort4(arr); end }
  x.report("sort5") { n.times do   ; ret = sort5(arr); end }
end


