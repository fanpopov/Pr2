# Проверка числа на простоту
def is_prime(p)
  return false if p <= 1
  return true if p <= 3
  return false if p % 2 == 0 || p % 3 == 0

  sqrt_p = Math.sqrt(p).to_i + 1
  (5..sqrt_p).step(6) do |i|
    return false if p % i == 0 || p % (i + 2) == 0
  end
  true
end

# Наибольший общий делитель
def gcd(a, b)
  while b != 0
    temp = b
    b = a % b
    a = temp
  end
  a
end

# Возведение в степень по модулю (a^x mod p)
def a_x_mod_p(a, x, p)
  result = 1
  a = a % p
  while x > 0
    result = (result * a) % p if x % 2 == 1
    x = x >> 1
    a = (a * a) % p
  end
  result
end

# Разложение числа на простые множители
def prime_factors(n)
  factors = []
  if n % 2 == 0
    factors << 2
    n /= 2 while n % 2 == 0
  end
  i = 3
  while i * i <= n
    if n % i == 0
      factors << i
      n /= i while n % i == 0
    end
    i += 2
  end
  factors << n if n > 2
  factors
end

# Проверка, является ли g примитивным корнем по модулю p
def is_primitive_root(g, p)
  return false if g == 1
  return false if gcd(g, p) != 1
  phi = p - 1
  factors = prime_factors(phi)
  factors.each do |q|
    return false if a_x_mod_p(g, phi / q, p) == 1
  end
  true
end

# Основная программа
begin
  srand Time.now.to_i

  # Генерация параметров для Диффи-Хеллмана
  p = 0
  loop do
    p = rand(1000..9999)
    break if is_prime(p)
  end

  g = 0
  loop do
    g = rand(1..(p - 1))
    break if is_primitive_root(g, p)
  end

  # Секретные ключи Алисы и Боба
  a = rand(1..(p - 2))
  b = rand(1..(p - 2))

  # Вычисление открытых ключей
  A = a_x_mod_p(g, a, p)
  B = a_x_mod_p(g, b, p)

  # Вычисление общего секретного ключа
  K1 = a_x_mod_p(B, a, p)
  K2 = a_x_mod_p(A, b, p)

  # Проверка, что ключи совпали
  if K1 != K2
    puts "Ошибка: ключи не совпали!"
    exit 1
  end

  # Запись результатов в файл
  File.open("output.txt", "w") do |out_file|
    out_file.puts "Параметры Диффи-Хеллмана:"
    out_file.puts "p = #{p}"
    out_file.puts "g = #{g}\n\n"
    out_file.puts "Секретный ключ Алисы (a) = #{a}"
    out_file.puts "Открытый ключ Алисы (A) = #{A}\n\n"
    out_file.puts "Секретный ключ Боба (b) = #{b}"
    out_file.puts "Открытый ключ Боба (B) = #{B}\n\n"
    out_file.puts "Общий секретный ключ (K) = #{K1}"
  end

  puts "Результаты записаны в output.txt"
rescue => e
  puts "Произошла ошибка: #{e.message}"
end
