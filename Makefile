.PHONY: clean All

All:
	@echo "----------Building project:[ CXml - Debug ]----------"
	@$(MAKE) -f  "CXml.mk"
clean:
	@echo "----------Cleaning project:[ CXml - Debug ]----------"
	@$(MAKE) -f  "CXml.mk" clean
