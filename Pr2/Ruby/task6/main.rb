require 'prime'

# Функции is_prime, gcd, a_x_mod_p, prime_factors, is_primitive_root
# такие же, как в задании 4 (здесь опущены для краткости)

begin
  srand Time.now.to_i

  # Генерация параметров p и g
  p = loop do
    val = rand(1000..9999)
    break val if is_prime(val)
  end

  g = loop do
    val = rand(1..(p - 1))
    break val if is_primitive_root(val, p)
  end

  # Секретные ключи
  a = rand(1..(p - 2))   # Алиса
  b = rand(1..(p - 2))   # Боб
  e = rand(1..(p - 2))   # Ева

  # Открытые ключи
  A = a_x_mod_p(g, a, p)
  B = a_x_mod_p(g, b, p)
  Ae = a_x_mod_p(g, e, p)   # подделка Евы
  Be = a_x_mod_p(g, e, p)

  # Вычисление ключей после подмены
  k_alice = a_x_mod_p(Be, a, p)
  k_bob   = a_x_mod_p(Ae, b, p)
  k_eve_alice = a_x_mod_p(Be, e, p)
  k_eve_bob   = a_x_mod_p(Ae, e, p)

  # Вывод результатов
  puts "Атака Man-in-the-Middle на протокол Диффи-Хеллмана"
  puts "Параметры: p = #{p}, g = #{g}\n\n"
  puts "Секретный ключ Алисы: a = #{a}"
  puts "Секретный ключ Боба  : b = #{b}"
  puts "Секретный ключ Евы   : e = #{e}\n\n"
  puts "Открытый ключ Алисы (A) = #{A}"
  puts "Открытый ключ Боба  (B) = #{B}"
  puts "Подменённый ключ от Евы (A') = #{Ae}"
  puts "Подменённый ключ от Евы (B') = #{Be}\n\n"
  puts "Ключ, вычисленный Алисой (K_Alice) = #{k_alice}"
  puts "Ключ, вычисленный Бобом   (K_Bob)   = #{k_bob}"
  puts "Ключ Евы с Алисой = #{k_eve_alice}"
  puts "Ключ Евы с Бобом   = #{k_eve_bob}\n\n"

  if k_alice == k_eve_alice && k_bob == k_eve_bob
    puts "Атака успешна: Ева имеет общие ключи с Алисой и Бобом."
  else
    puts "Ошибка атаки."
  end

  # Запись в файл
  File.open("mitm_output.txt", "w") do |f|
    f.puts "Атака Man-in-the-Middle на протокол Диффи-Хеллмана"
    f.puts "Параметры: p = #{p}, g = #{g}\n\n"
    f.puts "Секретный ключ Алисы: a = #{a}"
    f.puts "Секретный ключ Боба  : b = #{b}"
    f.puts "Секретный ключ Евы   : e = #{e}\n\n"
    f.puts "Открытый ключ Алисы (A) = #{A}"
    f.puts "Открытый ключ Боба  (B) = #{B}"
    f.puts "Подменённый ключ от Евы (A') = #{Ae}"
    f.puts "Подменённый ключ от Евы (B') = #{Be}\n\n"
    f.puts "Ключ, вычисленный Алисой (K_Alice) = #{k_alice}"
    f.puts "Ключ, вычисленный Бобом   (K_Bob)   = #{k_bob}"
    f.puts "Ключ Евы с Алисой = #{k_eve_alice}"
    f.puts "Ключ Евы с Бобом   = #{k_eve_bob}\n\n"
    if k_alice == k_eve_alice && k_bob == k_eve_bob
      f.puts "Атака успешна: Ева имеет общие ключи с Алисой и Бобом."
    else
      f.puts "Ошибка атаки."
    end
  end

  puts "Результаты атаки записаны в mitm_output.txt"
rescue => e
  puts "Ошибка: #{e.message}"
end
