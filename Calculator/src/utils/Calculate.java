package utils;

import java.util.ArrayList;
import java.util.Arrays;

import ui.CTextField;

public class Calculate {
	private static int textLength = 13;

	/**
	 * 功能实现
	 * @param ope
	 * @param numField
	 * @param formulaField
	 * @throws ArithmeticException
	 */
	public static void callMethod(String ope, CTextField numField, CTextField formulaField) throws ArithmeticException {
		String num = "";
		String result = "";
		String formula = "";
		switch (ope) {
		case "C":
			numField.setContent("0");
			numField.setFlag(true);
			formulaField.setContent("");
			formulaField.setFlag(true);
			break;
		case "CE":
			numField.setContent("0");
			break;
		case "X":
			String str = backSpace(numField.getContent());
			formulaField.setFlag(false);
			numField.setFlag(false);
			numField.setContent(str);
			break;
		case "=":
			result = equalFunction(numField, formulaField);
			numField.setContent(result);
			formula = formulaField.getContent();
			if (!"".equals(formula)) {
				int index = Tool.getLastOperatorIndex(formula)+1;
				if(index != formula.length()+1)
					formulaField.setLastOperand(formula.substring(index));
			}
			formulaField.setContent("");
			formulaField.setFlag(true);
			numField.setFlag(true);
			break;
		case "x²":
		case "¹/x":
		case "√":
		case "±":
			// 获取表达式的最后一个操作数
			String operand = Tool.getFormulaLastOperand(formulaField.getContent());
			num = numField.getContent();
			// 如果操作
			if (!Tool.isNumber(operand) && !"".equals(operand)) {
				num = operand;
			}
			String temp = "";
			if (ope == "x²") {
				temp = String.format("%s(%s) ", "sqr", num);
			} else if (ope == "¹/x") {
				temp = String.format("%s/(%s) ", "1", num);
			} else if (ope == "√") {
				temp = String.format("%s(%s) ", ope, num);
			} else if (ope == "±") {
				temp = String.format("%s(%s) ", "negate", num);
			}
			if (!Tool.isNumber(operand) && !"".equals(operand)) {
				operand = operand.replaceAll("\\(", "\\\\(");
				operand = operand.replaceAll("\\)", "\\\\)");
				formulaField.setContent(formulaField.getContent().replaceFirst(operand, temp));
			} else {
				formulaField.addContent(temp);
			}
			result = complexOperation(temp.trim());
			numField.setContent(result);
			formulaField.setFlag(false);
			break;
		}
	}

	/**
	 * 计算式求解
	 * @param formula
	 * @return
	 */
	public static String calculate(String formula) throws ArithmeticException{
//		int index = Tool.getLastOperatorIndex(formula);
//		formula = formula.substring(0, index);
		ArrayList<String> array = new ArrayList<String>(Arrays.asList(formula.split(" ")));
		if(Tool.isOperator(array.get(array.size()-1))) {
			array.remove(array.size()-1);
		}
		ArrayList<String> operands = new ArrayList<>();
		ArrayList<String> opes = new ArrayList<>();
		for (String s : array) {
			if(Tool.isOperator(s)) 
				opes.add(s);
			else
				operands.add(s);
		}
		String a = operands.get(0);
		if(!Tool.isNumber(a))
			a = complexOperation(a);
		String result = a;
		for (int i = 0; i < opes.size(); i++) {
			String b = operands.get(i+1);
			String ope = opes.get(i);
			if (!Tool.isNumber(a))
				a = complexOperation(a);
			else if (!Tool.isNumber(b))
				b = complexOperation(b);
			result = Calculate.arithmetic(Double.valueOf(a), ope, Double.valueOf(b));
			a = result;
		}
		return formatResult(result);
	}

	/**
	 * 复杂运算，如：开方、平方、求倒等
	 * @param formula
	 * @return
	 */
	public static String complexOperation(String formula) throws ArithmeticException{
		String regex = "\\(|\\)";
		String[] array = formula.split(regex);
		ArrayList<String> list = new ArrayList<>(Arrays.asList(array));
		list = Tool.removeEmpty(list);
		// 将最后一个数值先赋值给result
		String result = list.remove(list.size() - 1);
		for (int i = 0; i < list.size(); i++) {
			double number = Double.parseDouble(result);
			switch (list.get(i)) {
			case "sqr":
				result = String.valueOf(Math.pow(Double.parseDouble(result), 2));
				break;
			case "√":
				if(number < 0) {
					throw new ArithmeticException("无效输入");
				}
				result = String.valueOf(Math.sqrt(Double.parseDouble(result)));
				break;
			case "1/":
				if(number == 0) {
					throw new ArithmeticException("除数不能为0");
				}
				result = String.valueOf(MathematicalOperation.divide(1.0, Double.parseDouble(result)));
				break;
			case "negate":
				result = String.format("%s", formatResult(String.valueOf(0-number)));
				break;
			}
		}
		return formatResult(result);
	}

	/**
	 * 四则运算
	 * @param a
	 * @param ope
	 * @param b
	 * @return
	 */
	public static String arithmetic(double a, String ope, double b) throws ArithmeticException{
		double result = 0;
		switch (ope) {
		case "+":
			result = MathematicalOperation.add(a, b);
			break;
		case "-":
			result = MathematicalOperation.subtract(a, b);
			break;
		case "×":
			result = MathematicalOperation.multiply(a, b);
			break;
		case "÷":
			result = MathematicalOperation.divide(a, b);
			break;
		}
		return formatResult(String.valueOf(result));
	}

	/**
	 * 等于功能
	 * @param numField
	 * @param formulaField
	 * @return
	 */
	public static String equalFunction(CTextField numField, CTextField formulaField) {
		String num = numField.getContent();
		String lastOperand = formulaField.getLastOperand();
		String formula = formulaField.getContent();
		if ("".equals(formula) && !"".equals(num)) {
			String temp = String.format("%s %s", num, lastOperand);
			return calculate(temp);
		} else if (!"".equals(formula) && "".equals(lastOperand)){
			return calculate(formulaField.getContent());
		} else {
  			formulaField.addContent(num);
			return calculate(formulaField.getContent());
		}
	}

	/**
	 * 退格功能
	 * @param text
	 * @return
	 */
	private static String backSpace(String text) {
		return text.equals("0") || text.equals("") ? "0" : text.substring(0, text.length() - 1);
	}

	/**
	 * 格式化结果
	 * @param result
	 * @return
	 */
	private static String formatResult(String result) {
		if (Tool.isInteger(result)) {
			return String.valueOf((int) Double.parseDouble(result));
		} else if (result.length() > textLength) {
			return result.substring(0, textLength);
		} else {
			return result;
		}
	}

}
