#ifndef __CONTAINER_H__
#define __CONTAINER_H__


template<class T>
class container
{
	public:
	
		virtual ~container() = 0;
	
		container() { numOfElemnts = 0; }
		
		container(const container& _container) { numOfElemnts = _container.numOfElemnts; }
		
		container& operator=(const container& _container) { numOfElemnts = _container.numOfElemnts; }
		
		virtual bool Append(const T* _element, unsigned int _index) = 0;
		
		virtual bool Prepend(const T* _element, unsigned int _index) = 0;
		
		virtual bool Contains(const T* _element)const = 0;
		
		virtual const T* Find(const T& _value)const = 0; 
		
		virtual int Index(const T* _element)const = 0;
		
		virtual bool Insert(const T* _element) = 0;
		
		virtual bool Remove(const T& _value) = 0;
		
		virtual void RemoveAll() = 0;
		
		virtual bool RemoveAndDelete(const T& _value) = 0;
		
		virtual void RemoveAndDeleteAll() = 0;
		
		int Count()const { return numOfElemnts; }
		
		bool IsEmpty()const { return (0 == numOfElemnts); }

	protected:
		
		void SetNumOfElements(unsigned int _numOfElemnts) { numOfElemnts = _numOfElemnts; }
	
	private:

		unsigned int numOfElemnts;
		

};

template<class T>
container<T>::~container() {}


#endif
