package com.cc.library.service;

import com.cc.library.domain.BackInfo;
import com.cc.library.domain.PageBean;
import com.cc.library.domain.Reader;

public interface BackService {

	public PageBean<BackInfo> findBackInfoByPage(int pageCode, int pageSize);

	public BackInfo getBackInfoById(BackInfo backInfo);

	public PageBean<BackInfo> queryBackInfo(String iSBN, String paperNO,int borrowId,int pageCode,int pageSize);

	public int addBackInfo(BackInfo backInfo);

	public PageBean<BackInfo> findMyBorrowInfoByPage(Reader reader,
			int pageCode, int pageSize);

}
