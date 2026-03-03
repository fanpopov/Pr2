def continued_fraction(a, b)
  coefficients = []
  while b != 0
    q = a / b
    coefficients << q
    r = a % b
    a, b = b, r
  end
  coefficients
end

def gcd(a, b)
  while b != 0
    r = b
    b = a % b
    a = r
  end
  a
end

def compact_solution(a, a0, b, b0)
  k = (a0 != 0 && b0 != 0) ? [a / a0, b / b0].min : 0
  puts "Одно компактное решение: a = #{a + a0 * k}, b = #{b - b0 * k}"
  puts "Компактное общее решение: a = #{a + a0 * k} + #{a0} * k, b = #{b - b0 * k} - #{b0} * k, где k - целое число."
end

def solve_diophantine(a, b, c)
  cf = continued_fraction(a, b)

  x, y = 0, 1
  x_prev, y_prev = 1, 0

  cf.each do |q|
    x, x_prev = x_prev - q * x, x
    y, y_prev = y_prev - q * y, y
  end

  d = gcd(a, b)

  if c % d != 0
    puts "Нет решений."
    return
  end

  k = c / d
  a0 = b / d
  b0 = a / d

  puts "Одно решение: x = #{x_prev * k}, y = #{y_prev * k}"
  puts "Общее решение: x = #{x_prev * k} + #{a0} * k, y = #{y_prev * k} - #{b0} * k, где k - целое число.\n"
  compact_solution(x_prev * k, a0, y_prev * k, b0)
end

puts "143x + 169y = 5\n"
solve_diophantine(143, 169, 5)
