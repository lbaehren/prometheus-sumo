require 'test/unit'

class TestCalculation < Test::Unit::TestCase

  # Test addition of two numbers
  def test_add
    assert_equal( 2, 1+1 )
  end

  # Test substraction of two numbers
  def test_sub
    assert_equal( 1, 2-1 )
  end

  # Test multiplication of two numbers
  def test_mult
    assert_equal( 4, 2*2 )
  end

  # Test multiplication of two numbers
  def test_division
    assert_equal( 2, 4/2 )
  end

end
