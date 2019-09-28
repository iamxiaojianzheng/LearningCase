package com.cc.library.service;

import com.cc.library.domain.Admin;
import com.cc.library.domain.Book;
import com.cc.library.domain.PageBean;

import net.sf.json.JSONObject;

public interface BookService {

	public PageBean<Book> findBookByPage(int pageCode, int pageSize);

	public boolean addBook(Book book);

	public Book getBookById(Book book);

	public Book updateBookInfo(Book updateBook);

	public PageBean<Book> queryBook(Book book, int pageCode, int pageSize);

	public int deleteBook(Book book);

	public JSONObject batchAddBook(String fileName, Admin admin);

	public String exportBook();

}
