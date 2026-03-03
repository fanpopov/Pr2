def is_prime(number)
  return false if number <= 1
  return true if number == 2 || number == 3
  return false if number % 2 == 0 || number % 3 == 0

  sqrt_num = Math.sqrt(number).to_i + 1
  max_divisor = (sqrt_num + 1) / 6
  (1..max_divisor).each do |i|
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

def simple_modular_exponentiation(base, exponent, modulus)
  exponent = exponent % (modulus - 1)
  return 1 if exponent == 0
  result = 1
  exponent.times do
    result = (result * base) % modulus
  end
  result
end

def convert_to_binary(number)
  binary_digits = []
  while number > 0
    binary_digits << number % 2
    number /= 2
  end
  binary_digits
end

def binary_modular_exponentiation(base, exponent, modulus)
  return 0 if modulus == 1
  base %= modulus
  result = 1
  while exponent > 0
    if exponent % 2 == 1
      result = (result * base) % modulus
    end
    base = (base * base) % modulus
    exponent /= 2
  end
  result
end

def fast_modular_exponentiation(base, exponent, modulus)
  return 1 % modulus if exponent == 0
  return 0 if modulus == 1

  bits_needed = Math.log2(exponent).ceil + 1
  power_table = Array.new(bits_needed)
  power_table[0] = base % modulus
  (1...bits_needed).each do |i|
    power_table[i] = (power_table[i-1] * power_table[i-1]) % modulus
  end

  binary_exponent = convert_to_binary(exponent)
  result = 1
  binary_exponent.each_with_index do |bit, i|
    if bit == 1
      result = (result * power_table[i]) % modulus
    end
  end
  result
end

def compute_gcd(a, b)
  while b != 0
    remainder = b
    b = a % b
    a = remainder
  end
  a
end

def perform_fermat_test(candidate, test_limit)
  if candidate <= 1 || (candidate % 2 == 0 && candidate != 2)
    return false
  end

  test_bases = [2, 3, 5, 7, 11, 13, 17, 19, 23]
  test_limit = [test_limit, test_bases.size].min

  (0...test_limit).each do |i|
    base = test_bases[i]
    next if base >= candidate

    if compute_gcd(candidate, base) != 1
      return false
    end
    if simple_modular_exponentiation(base, candidate-1, candidate) != 1
      return false
    end
  end
  true
end

def validate_modulus(modulus, test_count)
  unless is_prime(modulus)
    puts "Ошибка: Модуль должен быть простым числом!"
    exit(1)
  end
  unless perform_fermat_test(modulus, test_count)
    puts "Ошибка: Модуль не прошел тест Ферма!"
    exit(1)
  end
  true
end

def run_all_tests
  raise "Test failed" unless fast_modular_exponentiation(3, 13, 7) == 3
  raise "Test failed" unless fast_modular_exponentiation(5, 13, 7) == 5
  raise "Test failed" unless fast_modular_exponentiation(5, 0, 7) == 1
  raise "Test failed" unless fast_modular_exponentiation(3, 100, 7) == 4
  raise "Test failed" unless fast_modular_exponentiation(3, 1, 7) == 3
  puts "Все тесты пройдены успешно!"
end

# Основная программа
if __FILE__ == $0
  begin
    run_all_tests
    print "Введите основание и показатель степени через пробел: "
    base1, exponent1 = gets.chomp.split.map(&:to_i)
    print "Введите второе основание и показатель степени через пробел: "
    base2, exponent2 = gets.chomp.split.map(&:to_i)
    print "Введите модуль (простое число): "
    modulus = gets.chomp.to_i
    print "Введите количество проверок для теста Ферма: "
    test_count = gets.chomp.to_i

    validate_modulus(modulus, test_count)

    result1 = fast_modular_exponentiation(base1, exponent1, modulus)
    result2 = fast_modular_exponentiation(base2, exponent2, modulus)

    if result1 == result2
      puts "#{base1}^#{exponent1} mod #{modulus} = #{base2}^#{exponent2} mod #{modulus}"
    else
      puts "#{base1}^#{exponent1} mod #{modulus} != #{base2}^#{exponent2} mod #{modulus}"
    end
  rescue => e
    puts "Произошла ошибка: #{e.message}"
  end
end
