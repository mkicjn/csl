(progn
  (declare 'nl '"
")
  (declare 'sp '" ")
  (declare 'colon ':)
  (declare 'backslash '\)
  (declare 'format (lambda '(f) '(cond (f (progn (print (car f)) (@ (cdr f)))))))
  (declare 'space (lambda '(l) '(cond ((cdr l) `(:(car l) :sp \(@ (cdr l)))) (t (list (car l))))))
  t)
