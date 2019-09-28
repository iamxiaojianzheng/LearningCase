package com.cc.library.dao;

import java.util.List;

import com.cc.library.domain.PageBean;
import com.cc.library.domain.Reader;
import com.cc.library.domain.ReaderType;

public interface ReaderDao {

	
	public Reader getReader(Reader reader);

	public Reader updateReaderInfo(Reader reader);

	public boolean addReader(Reader reader);

	public PageBean<Reader> findReaderByPage(int pageCode, int pageSize);

	public Reader getReaderById(Reader reader);

	public boolean deleteReader(Reader reader);

	public PageBean<Reader> queryReader(Reader reader,int pageCode, int pageSize);

	public Reader getReaderBypaperNO(Reader reader);

	public int batchAddReader(List<Reader> readers,List<Reader> failReaders);

	public List<Reader> findAllReaders();

}
