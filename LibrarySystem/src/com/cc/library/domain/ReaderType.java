package com.cc.library.domain;

import java.io.Serializable;
import java.util.Set;

public class ReaderType implements Serializable{

	private Integer readerTypeId;
	private String readerTypeName;//读者类型名称
	private Integer maxNum;	//最大借书量
	private Double penalty;	//每日罚金
	private Integer bday;	//可借天数
	private Integer renewDays;	//续借天数
	
	public Integer getReaderTypeId() {
		return readerTypeId;
	}
	public void setReaderTypeId(Integer readerTypeId) {
		this.readerTypeId = readerTypeId;
	}
	public String getReaderTypeName() {
		return readerTypeName;
	}
	public void setReaderTypeName(String readerTypeName) {
		this.readerTypeName = readerTypeName;
	}
	public Integer getMaxNum() {
		return maxNum;
	}
	public void setMaxNum(Integer maxNum) {
		this.maxNum = maxNum;
	}
	public Double getPenalty() {
		return penalty;
	}
	public void setPenalty(Double penalty) {
		this.penalty = penalty;
	}
	public Integer getBday() {
		return bday;
	}
	public void setBday(Integer bday) {
		this.bday = bday;
	}
	public ReaderType() {

	}
	
	
	
	public Integer getRenewDays() {
		return renewDays;
	}
	public void setRenewDays(Integer renewDays) {
		this.renewDays = renewDays;
	}


	
	
	
	

}
