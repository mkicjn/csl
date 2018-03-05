(progn
  	~ General functions ~
  (define 'reducea (lambda '(f a l) '(cond (l (@ f (f a (car l)) (cdr l))) (t a))))
  (declare 'reduce (lambda '(f l) '(reducea f (f (car l) (car (cdr l))) (cdr (cdr l)))))
  (declare 'mapcar (lambda '(f l) '(cond (l (cons (f (car l)) (@ f (cdr l)))))))
  (declare 'desc (lambda '(o l) '(cond ((null o) l) ((eq (car o) 'a) (@ (cdr o) (car l))) ((eq (car o) 'd) (@ (cdr o) (cdr l))))))
  (declare 'nthcdr (lambda '(n l) '(cond ((null l) l) ((> n 0) (@ (- n 1) (cdr l))) (t l))))
  (declare 'nth (lambda '(n l) '(car (nthcdr n l))))
  (declare 'randelt (lambda '(l) '(nth (random (length l)) l)))
  (declare 'range (lambda '(stt stp end) '(cond ((not ((cond ((> stp 0) >) ((< stp 0) <)) stt end)) (cons stt (@ (+ stt stp) stp end))))))
  (declare 'iota (lambda '(n) '(range 1 1 n)))
  (declare '! (lambda '(n) '(cond ((> n 1) (* n (@ (- n 1)))) (t 1))))
  (declare 'equal (lambda '(l1 l2) '(cond ((and (atom l1) (atom l2)) (eq l1 l2))
					  ((not (or (atom l1) (atom l2))) (and (@ (car l1) (car l2)) (@ (cdr l1) (cdr l2)))))))
  (declare 'remove-if (lambda '(f l) '(cond ((null l) nil) ((f (car l)) (@ f (cdr l))) (t (cons (car l) (@ f (cdr l)))))))
  (declare 'remove-if-not (lambda '(f l) '(cond ((null l) nil) ((f (car l)) (cons (car l) (@ f (cdr l)))) (t (@ f (cdr l))))))
  (declare 'sumlist (lambda '(l) '(reduce + l)))
  (declare 'sum (lambda variadic '(reduce + argv)))
  (declare 'ntimes (lambda '(n f) '(cond ((> n 0) `(:f \(@ (- n 1) f))))))

  	~ Macros ~
  (define 'letl (lambda '(p) '(cond (p (cons `(define :(car (car p)) :(car (cdr (car p)))) (@ (cdr p)))))))
  (declare 'let (lambda '(p) (quote `(progn \(letl p)))))
  (declare 'defun (lambda '(s a b) (quote `(declare :`(quote :s) :`(lambda :`(quote :a) :`(quote :b))))))
  (declare 'apply (lambda '(f a) (quote `(:f \a))))
  (declare 'funcall (lambda variadic (quote `(:(car argv) \(cdr argv)))))
  (declare 'dotimes (lambda '(n f) (quote `(progn \(ntimes n f)))))

	~ Formatted output ~
  (declare 'nl '"
")
  (declare 'sp '" ")
  (declare 'colon ':)
  (declare 'backslash '\)
  (declare 'format (lambda '(f) '(cond (f (progn (print (car f)) (@ (cdr f)))))))
  (declare 'space (lambda '(l) '(cond ((cdr l) `(:(car l) :sp \(@ (cdr l)))) (t (list (car l))))))
  t)
