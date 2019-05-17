package test;

import java.util.ArrayList;
import java.util.Arrays;

import utils.Calculate;
import utils.Tool;

public class Test {

	public static void main(String[] args) throws Exception{
//		System.out.println(Tool.isNumeric("."));
//		System.out.println(Tool.isOperator("/"));
//		System.out.println(Tool.formatNumeric("1234.123456"));
//		System.out.println(Math.sqrt(2));
//		System.out.println(Calculate.calculate("0.33 + 0.2 - 0 + 2 + 4 + 0.25 - -0"));
//		System.out.println(Tool.getFormulaLastOperand("1 + 2 - 3 × 4 ÷ 5 + 6 - 7 × 8 ÷ 1/(sqr(9))"));
//		System.out.println(Tool.getNumeric("1/(sqr(√(9.1)))"));
//		System.out.println(Arrays.toString("1/(sqr(9))".split("\\(|\\)")));
//		System.out.println(Math.pow(1.0 / Math.sqrt(2), 2));
//		System.out.println(Arrays.toString("1 + 2 - 3 × 4 ÷ 5 + 6 - 7 × 8 ÷ 1/(sqr(9))".split("[+\\-×÷]")));
//		System.out.println(Arrays.toString("1 + 2 - 3 × 4 ÷ 5 + 6 - 7 × 8 ÷ 1/(sqr(9))".split("[^+\\-×÷]")));
//		System.out.println(Arrays.toString("+-*/".split("")));
		System.out.println(Calculate.calculate("1 + 2 - 3 × 4 ÷ 5 + 6 - 7 × sqr(8)"));
//		System.out.println("1 +√(2) ".replaceFirst("√\\(2\\)", "sqr(√(2))"));
//		System.out.println("123".substring(1));
//		System.out.println(Tool.isFormula("1+2+"));
	}
}
