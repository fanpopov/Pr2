def fast_exponentiation_mod(base, exponent, modulus)
  reduced_exponent = exponent % (modulus - 1) # применение теоремы Ферма
  result = 1
  (1..reduced_exponent).each do |i|
    result = (result * base) % modulus
  end
  result
end

def gcd(a, b)
  while b != 0
    temp = b
    b = a % b
    a = temp
  end
  a
end

def fermats_test(prime_candidate, test_count)
  if prime_candidate <= 1 || (prime_candidate % 2 == 0 && prime_candidate != 2)
    return false
  end
  test_bases = [2, 3, 5, 7, 11, 13, 17, 19, 23]
  if test_count > test_bases.size
    test_count = test_bases.size
  end
  (0...test_count).each do |i|
    current_base = test_bases[i]
    next if current_base >= prime_candidate
    if gcd(prime_candidate, current_base) != 1
      return false
    end
    if fast_exponentiation_mod(current_base, prime_candidate-1, prime_candidate) != 1
      return false
    end
  end
  true
end

def is_prime(number)
  if number <= 1 || number % 2 == 0 || number % 3 == 0
    return false
  end
  sqrt_num = Math.sqrt(number).to_i + 1
  max_divisor = (sqrt_num + 1) / 6
  (1...max_divisor).each do |i|
    divisor1 = 6 * i - 1
    divisor2 = 6 * i + 1
    if divisor1 <= sqrt_num && number % divisor1 == 0
      return false
    end
    if divisor2 <= sqrt_num && number % divisor2 == 0
      return false
    end
  end
  true
end

def run_tests
  raise "Test failed" unless fast_exponentiation_mod(3, 100, 7) == 4
  raise "Test failed" unless gcd(1234, 54) == 2
  raise "Test failed" unless is_prime(23)
  puts "All tests passed!"
end

def validate_modulus(modulus, test_count)
  unless is_prime(modulus)
    puts "Модуль не является простым числом."
    return false
  end
  unless fermats_test(modulus, test_count)
    puts "Модуль не удовлетворяет тесту Ферма."
    return false
  end
  true
end

# Основная программа
begin
  run_tests
  print "Введите первое число и его степень через пробел: "
  base1, exponent1 = gets.chomp.split.map(&:to_i)
  print "Введите второе число и его степень через пробел: "
  base2, exponent2 = gets.chomp.split.map(&:to_i)
  print "Введите модуль: "
  modulus = gets.chomp.to_i
  print "Введите количество проверок для теоремы Ферма: "
  test_count = gets.chomp.to_i

  unless is_prime(modulus)
    puts "\nМодуль не является простым числом, попробуйте другой. Модуль обязательно должен быть > 0!"
    exit
  end
  unless fermats_test(modulus, test_count)
    puts "\nМодуль не удовлетворяет условию Ферма, попробуйте другой."
    exit
  end

  result1 = fast_exponentiation_mod(base1, exponent1, modulus)
  result2 = fast_exponentiation_mod(base2, exponent2, modulus)

  if result1 == result2
    puts "#{base1}^#{exponent1} mod #{modulus} = #{base2}^#{exponent2} mod #{modulus}"
  else
    puts "#{base1}^#{exponent1} mod #{modulus} != #{base2}^#{exponent2} mod #{modulus}"
  end
rescue => e
  puts "Произошла ошибка: #{e.message}"
end
