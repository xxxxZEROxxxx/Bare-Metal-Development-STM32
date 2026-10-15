The normal sequence is:
1. EXTI sets PR0.
2. The NVIC receives the request and marks EXTI0 pending.
3. The processor accepts EXTI0.
4. The NVIC clears its pending state and marks the interrupt active.
5. Your ISR executes.
6. Your ISR clears EXTI_PR.PR0.
7. The ISR returns, and the NVIC clears the active state as part of exception return.

