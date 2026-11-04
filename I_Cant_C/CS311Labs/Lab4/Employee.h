class Employee {
    private:
        int baseSalary;
        int hourlyRate;

        // made private since we have no current need to use publicly:
        int calculateWage(int extraHours);
        void setBaseSalary(int val); 
        void setHourlyRate(int val);
    public:
        Employee();
        Employee(int baseSalary, int hourlyRate);
        
        // int getBaseSalary(); // currently unneeded
        // int getHourlyRate();

        void printWage(const char* label, int extraHours);
        void setValsFromInput();
};