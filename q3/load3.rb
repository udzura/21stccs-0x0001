system "dd if=/dev/urandom of=/vagrant/dummy-#{$$} count=300k 2>/dev/null"

system "rm -f /vagrant/dummy-#{$$}"
