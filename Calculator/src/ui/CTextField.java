package ui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;

import javax.swing.JTextField;

import utils.Tool;

public class CTextField extends JTextField {

	private static final long serialVersionUID = 1L;
	// 暂存用户输入信息
	private StringBuffer content = new StringBuffer();
	// 存储最后一个操作数
	private String lastOperand = new String();
	// 判断用户输入是否为更新输入
	private boolean flag = true;
	
	public CTextField(String text, int columns) {
		super(text, columns);
	}
	
	public void init(Font font, int width, int height,
			Color backgroundColor, Color foregroundColor) {
		this.setFont(font);
		this.setPreferredSize(new Dimension(width, height));
		this.setBackground(backgroundColor);
		this.setForeground(foregroundColor);
	}

	public String getContent() {
		return content.toString();
	}

	public void setContent(String content) {
		this.content.replace(0, this.content.length(), content);
	}

	public void setContent(StringBuffer content) {
		this.content.replace(0, this.content.length(), content.toString());
	}
	
	public void addContent(String content) {
		this.content.append(content);
	}
	
	public void addContent(StringBuffer content) {
		this.content.append(content);
	}
	
	public void show() {
		String temp = this.content.toString();
		if(Tool.isNumeric(temp)) {
			this.setText(Tool.formatNumeric(temp));
		}
		this.setText(this.content.toString());
		System.out.println("content:"+this.content);
		System.out.println("lastOperand:"+this.lastOperand);
	}

	/**
	 * 如果content为0，则返回true
	 * @return
	 */
	public boolean isFlag() {
		return this.flag;
	}

	public String getLastOperand() {
		return lastOperand;
	}

	public void setLastOperand(String lastOperand) {
		this.lastOperand = lastOperand;
	}

	public void setFlag(boolean flag) {
		this.flag = flag;
	}

}
