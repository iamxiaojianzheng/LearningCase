package com.cc.library.dao;

import java.util.List;

import com.cc.library.domain.Book;
import com.cc.library.domain.BookType;
import com.cc.library.domain.PageBean;

public interface BookDao {



	public PageBean<Book> findBookByPage(int pageCode, int pageSize);

	public boolean addBook(Book book);


	public Book getBookById(Book book);

	public Book updateBookInfo(Book updateBook);

	public PageBean<Book> queryBook(Book book, int pageCode, int pageSize);

	public boolean deleteBook(Book book);

	public Book getBookByISBN(Book book);

	public int batchAddBook(List<Book> books, List<Book> failBooks);


	public List<Book> findAllBooks();

}
