package utils;

import java.util.ArrayList;
import java.util.regex.*;

public class Tool {

	/**
	 * 判断是否为正常的表达式
	 * @param formula
	 * @return
	 */
	public static boolean isFormula(String formula) {
		String regex = "(-?\\d+\\.?\\d*[+\\-×÷]-?\\d+\\.?\\d*)";
		return Pattern.matches(regex, formula);
	}
	
	/**
	 * 判断字符串是否为数值
	 * @param str
	 * @return
	 */
	public static boolean isNumber(String str) {
		String regex = "-?\\d+\\.?\\d*";
		return Pattern.matches(regex, str);
	}
	
	/**
	 * 判断字符串是否为整数
	 * @param str
	 * @return
	 */
	public static boolean isInteger(String str) {
		String regex = "-?\\d+(\\.0)?";
		return Pattern.matches(regex, str);
	}
	
	/**
	 * 判断字符串是否为数字或者小数点
	 * @param str
	 * @return
	 */
	public static boolean isNumeric(String str) {
		String regex = "[\\d.]";
		return Pattern.matches(regex, str);
	}
	
	/**
	 * 判断字符串是否为操作符
	 * @param str
	 * @return
     */
	public static boolean isOperator(String str) {
		String regex = "[+\\-×÷]";
		return Pattern.matches(regex, str);
	}
	
	/**
	 * 格式化数字，如11111，格式化为11,111
	 * @param str
	 * @return
	 */
	public static String formatNumeric(String str) {
		if (str.length() < 4) {
			return str;
		}
		// 小数点索引
		int decimalPointIndex = str.indexOf(".");
		// 小数部分
		String decimal = "";
		
		if (decimalPointIndex != -1) {			
			// 小数部分
			decimal = str.substring(decimalPointIndex);
			// 整数部分
			str = str.substring(0, decimalPointIndex);
		}
		StringBuffer sb = new StringBuffer(str);
		sb.reverse();
		int tag = 3;	// 每隔三个字符
		for (int i = tag; i < sb.length(); i+=4) {
			sb.insert(i, ",");
		}
		return sb.reverse().toString()+decimal;
	}
	
	/**
	 * 格式化计算式
	 * @param formula
	 * @return
	 */
	public static String formatFormula(String formula) {
		String[] key = new String[] {" ", "--", "\\+-", "\\+\\+", "-\\+"};
		String[] value = new String[] {"", "+", "-", "+", "-"};
		for (int i = 0; i < key.length; i++) {
			formula = formula.replaceAll(key[i], value[i]);
		}
		return formula;
	}
	
	/**
	 * 获取计算式中的最后一个操作数
	 * @param formula
	 * @return
	 */
	public static String getFormulaLastOperand(String formula) {
		int index = getLastOperatorIndex(formula);
		if(index == formula.length())
			return formula;
		return formula.substring(index+1).trim();
	}
	
	/**
	 * 获取计算式中的最后一个运算符
	 * @param formula
	 * @return
	 */
	public static int getLastOperatorIndex(String formula) {
		String regex = "[+\\-×÷]";
		Matcher matcher = getMatcher(regex, formula);
		String ope = "";
		while(matcher.find()) {
			ope = matcher.group();
		}
		int index = formula.lastIndexOf(ope);
		return "".equals(ope) ? formula.length() : index;
	}
	
	/**
	 * 获取数字部分
	 * @param formula
	 * @return
	 */
	public static String getNumeric(String formula) {
		String regex = "\\d+\\.?\\d*";
		Matcher matcher = getMatcher(regex, formula);
		String number = "";
		while(matcher.find()) {
			number =  matcher.group();
		}
		return number;
	}
	
	/**
	 * 获取Matcher对象
	 * @param regex
	 * @param str
	 * @return
	 */
	public static Matcher getMatcher(String regex, String str) {
		Pattern pattern = Pattern.compile(regex);
		Matcher matcher = pattern.matcher(str);
		return matcher;
	}
	
	/**
	 * 去空值
	 * @param array
	 * @return
	 */
	public static ArrayList<String> removeEmpty(ArrayList<String> array){
		ArrayList<String> list = new ArrayList<>();
		for (String s : array) {
			if(!Pattern.matches("\\s", s))
				list.add(s);
		}
		return list;
	}
}
