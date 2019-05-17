package ui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JButton;

public class CButton extends JButton {

	private static final long serialVersionUID = 1L;
	private Color backgroundColor;
	private Color pressedColor;
	private Color enteredColor;
	
	public CButton(String text) {
		super(text);
	}
	
	public void init(Font font, int width, int height,
			Color backgroundColor, Color foregroundColor, Color pressedColor, Color enteredColor) {
		this.setFont(font);
		this.setPreferredSize(new Dimension(width, height));
		this.setBackground(backgroundColor);
		this.setForeground(foregroundColor);
		// 注册事件监听
		this.addMouseListener(new CButtonMouseListener());
		this.addKeyListener(new CButtonKeyListener());
		this.backgroundColor = backgroundColor;
		this.pressedColor = pressedColor;
		this.enteredColor = enteredColor;
	}
	
	class CButtonMouseListener implements MouseListener {
		@Override
		public void mouseClicked(MouseEvent e) {
			JButton button = (JButton) e.getSource();
			button.setBackground(enteredColor);
		}

		@Override
		/**
		 * 在组件上按下鼠标按钮时调用。
		 */
		public void mousePressed(MouseEvent e) {
			JButton button = (JButton) e.getSource();
			button.setBackground(new Color(255, 206, 66));
		}

		@Override
		public void mouseReleased(MouseEvent e) {
			JButton button = (JButton) e.getSource();
			button.setBackground(new Color(255, 206, 66));
		}

		@Override
		/**
		 * 鼠标进入组件时调用。
		 */
		public void mouseEntered(MouseEvent e) {
			JButton button = (JButton) e.getSource();
			button.setBackground(enteredColor);
		}

		@Override
		/**
		 * 鼠标退出组件时调用。
		 */
		public void mouseExited(MouseEvent e) {
			JButton button = (JButton) e.getSource();
			button.setBackground(backgroundColor);
		}
	}
	
	class CButtonKeyListener implements KeyListener {		
		@Override
		/**
		 * 敲击键盘，发生在按键按下后，按键放开前。 
		 */
		public void keyTyped(KeyEvent e) {
			JButton button = (JButton) e.getSource();
			button.setBackground(pressedColor);
		}
		
		@Override
		public void keyPressed(KeyEvent e) {
			
		}
		
		@Override
		public void keyReleased(KeyEvent e) {
			
		}
	}
	
}
