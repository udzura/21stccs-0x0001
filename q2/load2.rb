require "net/http"
require "uri"

target = URI.parse "http://udzura.jp/"
100.times do
  Net::HTTP.get target
end
puts "OK"
