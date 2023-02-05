$scene:
	from $data read $2

pick up (from $data [$2,$4]):
	to $data write (from $data @param) at $1

pick up $2:
	to $script write false at $4


