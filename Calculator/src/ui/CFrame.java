package ui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollBar;

import com.sun.jna.platform.WindowUtils;

import utils.Calculate;
import utils.Tool;

public class CFrame extends JFrame {

	private static final long serialVersionUID = 1L;

	// 外观参数
	private Color bgTextField = new Color(230, 230, 230);
	private Color fgTextField = new Color(0, 0, 0);
	private Color bgButton = new Color(244, 244, 244);
	private Color fgButton = new Color(0, 0, 0);
	private Color bgNumberButton = new Color(251, 251, 251);
	private Color enteredColor = new Color(212, 213, 212);
	private Color pressedColor = new Color(189, 189, 189);
	private Color bgButtonPanel = new Color(228, 228, 228);
	private int fontSize = 20;
	private Font normalFont = new Font("Microsoft YaHei UI", Font.PLAIN, fontSize);
	private Font numberFont = new Font("Microsoft YaHei UI", Font.BOLD, fontSize + 10);
	private Font opeFont = new Font("Microsoft YaHei UI", Font.PLAIN, fontSize + 10);
	private Font numTextFont = new Font("Microsoft YaHei UI", Font.BOLD, 50);
	private Font formulaFont = new Font("Microsoft YaHei UI", Font.PLAIN, 20);

	/*布局对象*/
	private GridLayout gridLayout = new GridLayout(6, 4, 5, 5);
	private BorderLayout borderLayout = new BorderLayout();
	/*组件*/
	private Container container;
	private JPanel textPanel;
	private JPanel buttonPanel;
	/*滚动条*/
	private JScrollBar scrollBar;
	// 存放所有按钮
	private CButton[] buttons;
	// 数字显示区
	private CTextField numField;
	// 计算式显示区
	private CTextField formulaField;

	/** 计算器上的键的显示名字 */
	private final String[] KEYS = { "％", "√", "x²", "¹/x", "CE", "C", "X", "÷", "7", "8", "9", "×", "4", "5", "6", "-",
			"1", "2", "3", "+", "±", "0", ".", "=" };

	public CFrame() {
		init();
	}

	public void init() {
		container = getContentPane();
		container.setLayout(borderLayout);

		// 初始化buttonPanel
		buttonPanel = new JPanel();
		buttonPanel.setLayout(gridLayout);
		buttonPanel.setBackground(bgButtonPanel);
		buttonPanel.setPreferredSize(new Dimension(400, 400));
		buttonPanel.setOpaque(false);

		// 初始化textPanel
		textPanel = new JPanel(new BorderLayout());
		textPanel.setBackground(bgButton);
		textPanel.setOpaque(false);

		// 初始化滚动条
		scrollBar = new JScrollBar(JScrollBar.HORIZONTAL);
		scrollBar.setMinimum(1);
		scrollBar.setMaximum(16);

		// 初始化formulaField
		formulaField = new CTextField("", 30);
		formulaField.init(formulaFont, 385, 25, bgTextField, fgTextField);
		formulaField.setHorizontalAlignment(CTextField.RIGHT);
		formulaField.setBorder(BorderFactory.createLineBorder(bgTextField));
		formulaField.setEditable(false);

		// 初始化textField
		numField = new CTextField("0", 30);
		numField.init(numTextFont, 400, 95, bgTextField, fgTextField);
		numField.setContent("0");
		numField.setHorizontalAlignment(CTextField.RIGHT);
		numField.setBorder(BorderFactory.createLineBorder(bgTextField));
		numField.setEditable(false);

		// 初始化buttons
		buttons = new CButton[KEYS.length];

		/* 初始化buttons中的按钮对象 */
		for (int index = 0; index < buttons.length; index++) {
			buttons[index] = new CButton(KEYS[index]);
			buttons[index].addActionListener(new ButtonActionEvent());
			// 去除边框
			buttons[index].setBorderPainted(false);
			// 给012345789.按钮设置样式
			if ("0123456789".indexOf(buttons[index].getActionCommand()) >= 0) {
				buttons[index].init(numberFont, 96, 66, bgNumberButton, fgButton, pressedColor, enteredColor);
			} else if ("+-×÷=".indexOf(buttons[index].getActionCommand()) >= 0) {
				buttons[index].init(opeFont, 96, 66, bgButton, fgButton, pressedColor, enteredColor);
			} else {
				buttons[index].init(normalFont, 96, 66, bgButton, fgButton, pressedColor, enteredColor);
			}
			buttonPanel.add(buttons[index]);
		}

		/* 组件添加 */
		textPanel.add(formulaField, BorderLayout.NORTH);
		textPanel.add(numField, BorderLayout.CENTER); // 将textField添加进textPanel面板														
		container.add(textPanel, BorderLayout.NORTH);
		container.add(buttonPanel, BorderLayout.CENTER);

		// 设置JFrame参数
		System.setProperty("sun.java2d.noddraw", "true");
		WindowUtils.setWindowAlpha(this, 0.9f);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Toolkit tool = getToolkit();    //得到一个Toolkit对象
		Image image = tool.getImage("./images/icon.png");
		setIconImage(image);          //给Frame设置图标
		setSize(404, 627);
		setTitle("计算器");
		setLocation(100, 100);
		setVisible(true);
		setResizable(false);
		setFocusable(true);

	}

	class ButtonActionEvent implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			CButton button = (CButton) e.getSource();
			String buttonText = button.getText();
			if (Tool.isNumeric(buttonText)) {
				if (numField.isFlag() && !".".equals(buttonText)) {
					numField.setContent(buttonText);
					numField.setFlag(false);
				} else {
					// 每点击数字按钮或者按下键盘上的数字按键，就将数字字符追加至content
					numField.addContent(buttonText);
				}
				numField.show();
			} else if (Tool.isOperator(buttonText)) {
				String formula = formulaField.getContent();
				int formulaLength = formula.length();
				String number = numField.getContent();
				// 如果计算式长度大于1，并且numField缓存为0，则进行运算符的修改
				if (formulaLength == 0){
					formulaField.addContent(String.format("%s %s ", number, buttonText));
				} else if (formulaLength > 1 && "0".equals(numField.getContent())) {
					String str = formula.substring(formulaLength - 2, formulaLength - 1);
					if (Tool.isOperator(str)) {
						formulaField.setContent(
								new StringBuffer(formula).replace(formulaLength - 2, formulaLength - 1, buttonText));
					}
				} else {
					String operand = Tool.getFormulaLastOperand(formulaField.getContent());
					if (!Tool.isNumber(operand) && !"".equals(operand)) {						
						formulaField.addContent(String.format("%s ", buttonText));
					} else {
						formulaField.addContent(String.format("%s %s ", number, buttonText));
					}
				}
				// numField.content则清空，记录下一个数字的输入
				numField.setContent(Calculate.calculate(formulaField.getContent()));
				numField.show();
				formulaField.show();
				numField.setFlag(true);
				numField.setContent("0");
			} else {
				try {
					Calculate.callMethod(buttonText, numField, formulaField);
					numField.show();
					formulaField.show();
//					if(numField.isFlag())
//						numField.setContent("0");
					if(formulaField.isFlag())
						formulaField.setContent("");
				} catch (ArithmeticException ex) {
					String message = ex.getMessage();
					if("BigInteger divide by zero".equals(ex.getMessage())) {
						message = "除数不能为零";
					}
					numField.setText(message);
					numField.setFlag(true);
				}
			}
		}
	}
}
