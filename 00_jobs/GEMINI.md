# Documentation Guidelines for Gemini

Follow these rules when generating or updating technical documentation in this repository:

## 1. Technical Style & Tone
- **Depth:** Target a "Staff Software Engineer" level of technical detail.
- **Clarity:** Use precise terminology (e.g., use "Hart" instead of "Core" when referring to RISC-V execution units).
- **Brevity:** Avoid fluff. Focus on architectural impact and implementation details.

## 2. Formatting Standards
### 2.1. Markdown files
- Use proper heading hierarchies (#, ##, ###).
- Before finalizing a document, check for sequential heading indices (e.g., ensuring 2.2 is followed by 2.3 or 3, not 4).
- Title should start with #.
- Heading 1 should start with ## followed by heading1_number. Syntax - (## <heading1_number>. <text>).
- Heading 2 should start with ### followed by heading1_number.heading2_number. Syntax - (### <heading1_number>.<heading2_number>. <text>).
- Heading 3 should start with #### followed by heading1_number.heading2_number.heading3_number. Syntax - (#### <heading1_number>.<heading2_number>.<heading3_number>. <text>).
- Validate that all internal anchor links are functional.

### 2.2. Code blocks
- Always specify the language (e.g., ` ```assembly `, ` ```c `).
- Use RISC-V ABI names (e.g., `a0`, `ra`, `sp`) rather than raw register numbers (`x10`, `x1`, `x2`) unless discussing the hardware encoding specifically.


### 2.3. Diagrams
- Use Mermaid.js syntax for sequence diagrams and flowcharts.
