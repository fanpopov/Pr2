def compute_gcd(a, b)
  while b != 0
    remainder = a % b
    a = b
    b = remainder
  end
  a
end

def find_modular_inverse(number, modulus, print_modulus)
  puts "------------------------"
  puts "Rem\tX\tY\tQuotient"
  puts "------------------------"

  prev_x = 1
  current_x = 0
  prev_y = 0
  current_y = 1
  remainder = 0
  quotient = 0
  a = number
  b = modulus

  while b != 0
    remainder = a % b
    quotient = a / b

    new_x = prev_x - quotient * current_x
    new_y = prev_y - quotient * current_y

    puts "#{remainder}\t#{new_x}\t#{new_y}\t#{quotient}"
    puts "------------------------"

    a = b
    b = remainder
    prev_x = current_x
    current_x = new_x
    prev_y = current_y
    current_y = new_y
  end

  prev_x += print_modulus if prev_x < 0
  prev_x
end

def check_coprimality(gcd_result)
  if gcd_result != 1
    puts "Ошибка: Число и модуль не взаимно просты, обратный элемент не существует."
    exit(1)
  end
end

# Основная программа
begin
  print "Введите число для нахождения обратного элемента: "
  number = gets.chomp.to_i
  print "Введите модуль: "
  modulus = gets.chomp.to_i

  check_coprimality(compute_gcd(number, modulus))
  inverse = find_modular_inverse(number, modulus, modulus)

  puts "Обратный элемент = #{inverse}"
  puts "#{number}^(-1) mod #{modulus} = #{inverse}"
  puts "#{number}*#{inverse} mod #{modulus} = #{(number * inverse) % modulus}"
rescue => e
  puts "Произошла ошибка: #{e.message}"
end
