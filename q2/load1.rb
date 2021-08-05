require "json"

ha = {}
1000.times do |i|
  ha["column-#{i}"] = {}
  10.times do |j|
    ha["column-#{i}"]["child-#{j}"] = rand(65536)
  end
end

str = JSON.dump ha
f = open("/vagrant/dummy.json", "w") do |f|
  f.puts str
end

100.times do
  if File.exist? "/vagrant/dummy.json"
    data = File.read "/vagrant/dummy.json"
    ha = JSON.load data
    1000.times do |i|
      10.times do |j|
        ha["column-#{i}"]["child-#{j}"] += 1
      end
    end

    str = JSON.dump ha
    f = open("/vagrant/dummy.json", "w") do |f|
      f.puts str
    end
  end
end

puts "OK"
