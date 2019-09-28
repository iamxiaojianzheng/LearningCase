package com.cc.library.action;

import org.apache.struts2.ServletActionContext;

import com.cc.library.domain.BackInfo;
import com.cc.library.domain.PageBean;
import com.cc.library.service.BackService;
import com.opensymphony.xwork2.ActionSupport;

public class BorrowSearchAction extends ActionSupport {

    private static final long serialVersionUID = 1L;

    private BackService backService;

    public void setBackService(BackService backService) {
        this.backService = backService;
    }

    private int pageCode;

    private String ISBN;

    private String paperNO;

    private int borrowId;

    public void setBorrowId(int borrowId) {
        this.borrowId = borrowId;
    }

    public void setISBN(String iSBN) {
        ISBN = iSBN;
    }

    public void setPaperNO(String paperNO) {
        this.paperNO = paperNO;
    }

    public void setPageCode(int pageCode) {
        this.pageCode = pageCode;
    }

    public String findBackInfoByPage() {
        // 获取页面传递过来的当前页码数
        if (pageCode == 0) {
            pageCode = 1;
        }
        // 给pageSize,每页的记录数赋值
        int pageSize = 5;
        PageBean<BackInfo> pb = backService.findBackInfoByPage(pageCode, pageSize);
        if (pb != null) {
            pb.setUrl("findBackInfoByPage.action?");
        }
        // 存入request域中
        ServletActionContext.getRequest().setAttribute("pb", pb);
        return "success";
    }

    public String queryBorrowSearchInfo() {
        // 获取页面传递过来的当前页码数
        if (pageCode == 0) {
            pageCode = 1;
        }
        // 给pageSize,每页的记录数赋值
        int pageSize = 5;
        PageBean<BackInfo> pb = null;
        if ("".equals(ISBN.trim()) && "".equals(paperNO.trim()) && borrowId == 0) {
            pb = backService.findBackInfoByPage(pageCode, pageSize);
        } else {
            pb = backService.queryBackInfo(ISBN, paperNO, borrowId, pageCode, pageSize);
        }
        if (pb != null) {
            pb.setUrl("queryBorrowSearchInfo.action?ISBN=" + ISBN + "&paperNO=" + paperNO + "&borrowId=" + borrowId
                    + "&");
        }
        ServletActionContext.getRequest().setAttribute("pb", pb);
        return "success";
    }
}
