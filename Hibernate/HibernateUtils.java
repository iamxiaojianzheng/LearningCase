import java.io.Serializable;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;
import org.hibernate.query.Query;

@SuppressWarnings("unchecked")
public class HibernateUtil {

	private static final ThreadLocal<Session> threadLocal = new ThreadLocal<Session>();
	private static SessionFactory sessionFactory;
	private static Session session;
	private static Transaction tx;

	static {
		try {
			Configuration configuration = new Configuration().configure();
			sessionFactory = configuration.buildSessionFactory();
		} catch (HibernateException e) {
			System.out.println("Initial SessionFactory creation failed.");
			e.printStackTrace();
		}
	}

	/**
	 * get sessionFactory
	 * 
	 * @return
	 */
	public static SessionFactory getSessionFactory() {
		return sessionFactory;
	}

	/**
	 * close sessionFactory
	 */
	public static void closeSessionFactory() {
		if (sessionFactory != null) {
			sessionFactory.close();
		}
	}

	/**
	 * get session
	 * 
	 * @return
	 * @throws HibernateException
	 */
	public static Session getSession() throws HibernateException {
		Session session = (Session) threadLocal.get();
		if (session == null || !session.isOpen()) {
			session = (sessionFactory != null) ? sessionFactory.getCurrentSession() : null;
		}
		threadLocal.set(session);
		return session;
	}

	/**
	 * add or update t
	 * 
	 * @param t
	 */
	public <T> void saveOrUpdate(T t) {
		try {
			session = getSession();
			tx = session.beginTransaction();
			session.saveOrUpdate(t);
			tx.commit();
		} catch (HibernateException e) {
			e.printStackTrace();
			tx.rollback();
		}
	}

	/**
	 * delete by id
	 * 
	 * @param entityClassName
	 * @param id
	 */
	public <T> void delete(Class<T> entityClass, Serializable id) {
		try {
			session = getSession();
			tx = session.beginTransaction();
			T obj = (T) session.get(entityClass, id);
			session.delete(obj);
			tx.commit();
		} catch (HibernateException e) {
			e.printStackTrace();
			tx.rollback();
		}
	}

	/**
	 * delete by t
	 * 
	 * @param t
	 */
	public <T> void delete(T t) {
		try {
			session = getSession();
			tx = session.beginTransaction();
			session.delete(t);
			tx.commit();
		} catch (HibernateException e) {
			e.printStackTrace();
			tx.rollback();
		}
	}

	/**
	 * get t by id
	 * 
	 * @param entityClass
	 * @param id
	 * @return
	 */
	public <T> T getById(Class<T> entityClass, Serializable id) {
		try {
			session = getSession();
			tx = session.beginTransaction();
			T t = session.get(entityClass, id);
			tx.commit();
			return t;
		} catch (HibernateException e) {
			e.printStackTrace();
			tx.rollback();
		}
		return null;
	}

	/**
	 * get all t
	 * 
	 * @param entityClassName
	 * @return
	 */
	public <T> List<T> getAll(String entityClassName) {
		String hql = "from " + entityClassName;
		try {
			session = getSession();
			tx = session.beginTransaction();
			Query<T> q = session.createQuery(hql);
			List<T> list = (List<T>) q.list();
			tx.commit();
			return list;
		} catch (HibernateException e) {
			e.printStackTrace();
			tx.rollback();
		}
		return null;
	}

	/**
	 * total count
	 * 
	 * @param entityClassName
	 * @return
	 */
	public int count(String entityClassName) {
		try {
			session = getSession();
			tx = session.beginTransaction();
			Long count = (Long) session.createQuery("select count(*) from " + entityClassName).uniqueResult();
			tx.commit();
			return count.intValue();
		} catch (HibernateException e) {
			e.printStackTrace();
			tx.rollback();
		}
		return -1;
	}

	/**
	 * get T objects by hql
	 * 
	 * @param hql
	 * @param params
	 * @return
	 */
	public <T> List<T> getByHql(String hql, Object[] params) {
		try {
			session = getSession();
			tx = session.beginTransaction();
			Query<T> q = session.createQuery(hql);
			for (int i = 0; i < params.length; i++) {
				q.setParameter(i, params[i]);
			}
			List<T> list = q.list();
			tx.commit();
			return list;
		} catch (HibernateException e) {
			e.printStackTrace();
		}
		return null;
	}
}
