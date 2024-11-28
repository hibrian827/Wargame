default:
	@echo "Please specify a target to make (deploy or debug)"

deploy: prob.c
	gcc prob.c -lpthread -o prob

debug: prob.c
	gcc prob.c -lpthread -o prob_debug -g
