package utils;

import java.math.BigDecimal;

/**
 * 四则运算
 */
public class MathematicalOperation {

    private static BigDecimal BigDecimal(double num1) {
        return new BigDecimal( num1 );
    }

    /**
     *  加法
     * @param num1
     * @param num2
     * @return
     */
    public static double add(double num1, double num2 ) {
        BigDecimal first = BigDecimal( num1 );
        BigDecimal second = BigDecimal( num2 );
        return first.add(second).doubleValue();
    }
    
    /**
     *  减法
     * @param num1
     * @param num2
     * @return
     */
    public static double subtract(double num1, double num2 ) {
        BigDecimal first = BigDecimal( num1 );
        BigDecimal second = BigDecimal( num2 );
        return first.subtract(second).doubleValue();
    }
    
    /**
     *  乘法
     * @param num1
     * @param num2
     * @return
     */
    public static double multiply(double num1, double num2 ) {
        BigDecimal first = BigDecimal( num1 );
        BigDecimal second = BigDecimal( num2 );
        return first.multiply(second).doubleValue();
    }
    
    /**
     *  除法
     * @param num1
     * @param num2
     * @return
     */
    public static double divide(double num1, double num2 ) {
        BigDecimal first = BigDecimal( num1 );
        BigDecimal second = BigDecimal( num2 );
        return first.divide(second, 20, BigDecimal.ROUND_HALF_UP).doubleValue();
    }
}