package com.cc.library.service.impl;

import java.util.Calendar;
import java.util.Date;
import java.util.List;

import com.cc.library.dao.BackDao;
import com.cc.library.dao.BookDao;
import com.cc.library.dao.BorrowDao;
import com.cc.library.dao.ForfeitDao;
import com.cc.library.dao.ReaderDao;
import com.cc.library.domain.BackInfo;
import com.cc.library.domain.Book;
import com.cc.library.domain.BorrowInfo;
import com.cc.library.domain.ForfeitInfo;
import com.cc.library.domain.PageBean;
import com.cc.library.domain.Reader;
import com.cc.library.service.BorrowService;

public class BorrowServiceImpl implements BorrowService{

	private BorrowDao borrowDao;
	private BookDao bookDao;
	private ReaderDao readerDao;
	private ForfeitDao forfeitDao;
	private BackDao backDao;
	
	
	
	
	

	public void setBackDao(BackDao backDao) {
		this.backDao = backDao;
	}

	public void setForfeitDao(ForfeitDao forfeitDao) {
		this.forfeitDao = forfeitDao;
	}

	public void setBookDao(BookDao bookDao) {
		this.bookDao = bookDao;
	}

	public void setReaderDao(ReaderDao readerDao) {
		this.readerDao = readerDao;
	}

	public void setBorrowDao(BorrowDao borrowDao) {
		this.borrowDao = borrowDao;
	}

	@Override
	public PageBean<BorrowInfo> findBorrowInfoByPage(int pageCode, int pageSize) {
		// TODO Auto-generated method stub
		return borrowDao.findBorrowInfoByPage(pageCode,pageSize);
	}

	@Override
	public BorrowInfo getBorrowInfoById(BorrowInfo info) {
		// TODO Auto-generated method stub
		return borrowDao.getBorrowInfoById(info);
	}

	
	@Override
	public int addBorrow(BorrowInfo info) {
		/*
		 * 1. 得到借阅的读者
		 * 
		 * 2. 查看读者输入的密码是否匹配
		 * 		2.1 如果不匹配提示 密码错误
		 * 		2.2 如果匹配,执行第3步骤
		 * 
		 * 3. 查看该读者的借阅信息
		 * 		3.1 查看借阅信息的条数
		 * 		3.2 查看该读者的类型得出该读者的最大借阅数量
		 * 		3.3 匹配借阅的数量是否小于最大借阅量
		 * 			3.3.1 小于,则可以借阅
		 * 			3.3.2 大于,则不可以借阅,直接返回借阅数量已超过
		 * 		3.4 查看读者的罚款信息,是否有未缴纳的罚款
		 * 			3.4.1 如果没有,继续第3的操作步骤
		 * 			3.4.2 如果有,直接返回有尚未缴纳的罚金
		 * 
		 * 4. 查看借阅的书籍
		 * 		4.1 查看该书籍的在馆数量是否大于1,,如果为1则不能借阅,必须留在馆内浏览
		 * 			4.1.1 如果大于1,进入第4操作步骤
		 * 			4.1.2 如果小于等于1,提示该图书为馆内最后一本,无法借阅
		 * 
		 * 5. 处理借阅信息
		 * 		5.1 得到该读者的最大借阅天数,和每日罚金
		 * 			5.1.1 获得当前时间
		 * 			5.1.2 根据最大借阅天数,计算出截止日期
		 * 			5.1.3 为借阅信息设置每日的罚金金额
		 * 		5.2 获得该读者的信息,为借阅信息设置读者信息
		 * 		5.3 获得图书信息,为借阅信息设置图书信息
		 * 		5.4 获得管理员信息,为借阅信息设置操作的管理员信息
		 * 
		 * 6. 存储借阅信息
		 * 
		 * 
		 * 
		 * 7. 借阅的书籍的在馆数量需要减少
		 * 
		 * 8. 生成归还记录
		 * 
		 */
		
		//得到密码
		String pwd = info.getReader().getPwd();
		//1. 得到借阅的读者
		Reader reader = readerDao.getReaderBypaperNO(info.getReader());
		
		//先检查属于的图书ISBN码和读者的证件号是否正确存在
		if(reader==null){
			return 2;//读者证件号有误
		}
		Book book = bookDao.getBookByISBN(info.getBook());
		if(book==null){
			return 3;//图书ISBN号码有误
		}
		
		
		//2. 查看读者输入的密码是否匹配
		if(!reader.getPwd().equals(pwd)){
			return -1;//返回-1表示密码错误
		}
		//3. 查看该读者的借阅信息
		List<BorrowInfo> readerInfos = borrowDao.getNoBackBorrowInfoByReader(reader);///查询的应该是未归还的记录
		//查看借阅信息的条数
		//查看该读者的类型得出该读者的最大借阅数量
		// 匹配借阅的数量是否小于最大借阅量
		if(readerInfos!=null && readerInfos.size()>=reader.getReaderType().getMaxNum()){
			return -2;	//返回借阅数量已超过
		}
		// 查看读者的罚款信息,是否有未缴纳的罚款
		List<ForfeitInfo> list = forfeitDao.getForfeitByReader(reader);
		for(ForfeitInfo forfeitInfo : list){
			if(forfeitInfo.getIsPay()==0){
				return -3;//尚未缴纳的罚金
			}
		}
		//4. 查看借阅的书籍
		// 查看该书籍的在馆数量是否大于1,,如果为1则不能借阅,必须留在馆内浏览
		Book bookByISBN = bookDao.getBookByISBN(info.getBook());
		if(bookByISBN.getCurrentNum()<=1){
			return -4;	//该图书为馆内最后一本,无法借阅
		}
		
		//5. 处理借阅信息
		//得到该读者的最大借阅天数,和每日罚金
		int maxDay = reader.getReaderType().getBday();//可借天数
		double penalty = reader.getReaderType().getPenalty();//每日罚金
		
		//获得当前时间
		Date borrowDate = new Date(System.currentTimeMillis());
		
		Calendar calendar = Calendar.getInstance();
		calendar.setTime(borrowDate);
		calendar.add(Calendar.DAY_OF_MONTH, +maxDay);//+maxDay今天的时间加maxDay天
		
		// 根据最大借阅天数,计算出截止日期
		Date endDate = calendar.getTime();
		
		//获得该读者的信息,为借阅信息设置读者信息
		BorrowInfo borrowInfo = new BorrowInfo();
		borrowInfo.setReader(reader);
		borrowInfo.setAdmin(info.getAdmin());
		borrowInfo.setBook(bookByISBN);
		borrowInfo.setBorrowDate(borrowDate);
		borrowInfo.setEndDate(endDate);
		borrowInfo.setPenalty(penalty);
	
		int id = borrowDao.addBorrow(borrowInfo);//返回1成功添加,返回0添加失败
		//在馆数量需要减少
		int state = 0;
		if(id!=0){
			bookByISBN.setCurrentNum(bookByISBN.getCurrentNum()-1);
			bookDao.updateBookInfo(bookByISBN);
			BackInfo info2 = new BackInfo();
			BorrowInfo borrowInfo2 = new BorrowInfo();
			borrowInfo2.setBorrowId(id);
			info2.setBorrowInfo(borrowInfo2);
			info2.setBorrowId(id);
			state = backDao.addBack(info2);
		}
		
		
		return state;
	}

	@Override
	public boolean checkBorrowInfo() {
		// 检查借阅表是否有逾期
		//主要步骤
		/*
		 *	1.得到所有的未归还的借阅记录(包括未归还,逾期未归还,续借未归还,续借逾期未归还)
		 *
		 * 	2.遍历所有的未归还的借阅记录(包括未归还,逾期为归还,续借为归还,续借逾期未归还)
		 * 
		 * 	3.查看当前时间和借阅的截止的时间的大小
		 *		3.1 如果小于,直接跳过
		 *		3.2如果大于则需要进行逾期处理的,进行第4步操作
		 *
		 *	4.用当前时间减去截止时间得到逾期的天数
		 *
		 *	5.为当前借阅记录设置逾期天数,并进行数据库修改
		 *
		 *	6.需要生成罚金记录
		 *		6.1 得到当前借阅记录的罚金金额,和当前的逾期天数进行相乘,得到罚金金额
		 *		6.2 将当前借阅记录的id和罚金的金额设置进新生成的罚金记录
		 *
		 *	7.设置当前借阅记录的状态
		 *		7.1 如果是未归还，则改为逾期未归还
		 *		7.2如果是续借未归还，则改为续借逾期未归还
		 *		7.3如果是逾期未归,则不改变
		 *		7.4如果是续借逾期不归还,则不改变
		 * 
		 */
		//得到所有的未归还的借阅记录(包括未归还,逾期为归还,续借为归还,续借逾期不归还)
		List<BorrowInfo> borrowInfos = borrowDao.getBorrowInfoByNoBackState();
		if(borrowInfos!=null){
			for (BorrowInfo borrowInfo : borrowInfos) {
				long time1 = borrowInfo.getEndDate().getTime();//截止时间
				long time2 = System.currentTimeMillis();//当前时间
				if(time2>time1){
					//当前时间大于截止时间,已经逾期
					Double days =Math.floor((time2-time1)/(24*60*60*1000));
					//用当前时间减去截止时间得到逾期的天数
					int day = days.intValue();
					//为当前借阅记录设置逾期天数,并进行数据库修改
					borrowInfo.setOverday(day);
					//设置当前借阅记录的状态
					if(borrowInfo.getState()==0){
						//如果是未归还，则改为逾期未归还
						borrowInfo.setState(1);
					}else if(borrowInfo.getState()==3){
						borrowInfo.setState(4);
					}
					//进行数据库修改
					borrowDao.updateBorrowInfo(borrowInfo);
					//需要生成罚金记录
					ForfeitInfo forfeitInfo = new ForfeitInfo();
					forfeitInfo.setBorrowId(borrowInfo.getBorrowId());
					forfeitInfo.setBorrowInfo(borrowInfo);
					// 得到当前借阅记录的罚金金额,和当前的逾期天数进行相乘,得到罚金金额
					double pay = borrowInfo.getPenalty() * day;
					//将当前借阅记录的id和罚金的金额设置进新生成的罚金记录
					forfeitInfo.setForfeit(pay);
					//生成的罚金记录
					boolean flag = forfeitDao.addForfeitInfo(forfeitInfo);
					if(!flag){
						return false;
						
					}
				}
			}
		}
		return true;
		
	}

	@Override
	public int renewBook(BorrowInfo borrowInfo) {
		//续借步骤：
		/*
		 * 1. 得到借阅的记录
		 * 
		 * 2. 得到借阅的记录的状态
		 * 		2.1 如果已经是续借状态(包括续借未归还,续借逾期未归还),则返回已经续借过了,返回-2
		 * 		2.2 如果是归还状态(包括归还,续借归还),则返回该书已还,无法续借,返回-1
		 *		2.3 如果都不是以上情况,则进行下一步。
		 * 
		 * 3. 得到借阅的读者
		 * 
		 * 4. 得到借阅的读者类型
		 * 
		 * 5. 得到可续借的天数
		 * 
		 * 6. 在当前记录的截止日期上叠加可续借天数
		 * 		6.1 如果叠加后的时候比当前时间小,则返回你已超续借期了,无法进行续借,提示读者快去还书和缴纳罚金  返回-3
		 * 		6.2如果大于当前时间进行下一步
		 * 
		 * 7. 得到当前借阅记录的状态
		 * 		7.1 如果当前记录为逾期未归还,则需要取消当前借阅记录的罚金记录,并将该记录的状态设置为续借未归还
		 * 		7.2 如果为未归还状态,直接将当前状态设置为续借未归还
		 * 
		 * 8. 为当前借阅记录进行设置,设置之后重新update该记录 返回1
		 */
		//得到借阅的记录
		BorrowInfo borrowInfoById = borrowDao.getBorrowInfoById(borrowInfo);
		//得到借阅的记录的状态
		Integer state = borrowInfoById.getState();
		if(state==3 || state==4){
			//如果已经是续借状态(包括续借未归还,续借逾期未归还),则返回已经续借过了,返回-2
			return -2;
		}
		if(state==2 || state==5){
			//如果是归还状态(包括归还,续借归还),则返回该书已还,无法续借,返回-1
			return -1;
		}
		//得到可续借的天数
		Integer renewDays = borrowInfoById.getReader().getReaderType().getRenewDays();
		//在当前记录的截止日期上叠加可续借天数
		Calendar calendar = Calendar.getInstance();
		calendar.setTime(borrowInfoById.getEndDate());
		calendar.add(Calendar.DAY_OF_MONTH, +renewDays);//+renewDays ,今天的时间加renewDays天
		// 根据可续借天数,计算出截止日期
		Date endDate = calendar.getTime();
		//设置截止时间
		borrowInfoById.setEndDate(endDate);
		if(System.currentTimeMillis()>endDate.getTime()){
			//如果叠加后的时候比当前时间小,则返回你已超续借期了,无法进行续借,提示读者快去还书和缴纳罚金  返回-3
			return -3;
		}
		
		//得到当前借阅记录的状态
		//如果当前记录为逾期未归还,则需要取消当前借阅记录的罚金记录,并将该记录的状态设置为续借未归还
		if(state==1){
			BackInfo backInfo = new BackInfo();
			backInfo.setBorrowId(borrowInfoById.getBorrowId());
			//删除该罚金记录
			boolean deleteBackInfo = backDao.deleteBackInfo(backInfo);
			if(!deleteBackInfo){
				return 0;
			}
		}
		//将当前状态设置为续借未归还
		borrowInfoById.setState(3);
		//为当前借阅记录进行设置,设置之后重新update该记录 返回1
		BorrowInfo updateBorrowInfo = borrowDao.updateBorrowInfo(borrowInfoById);
		if(borrowInfo!=null){
			return 1;
		}
		
		return 0;
	}

	
}
