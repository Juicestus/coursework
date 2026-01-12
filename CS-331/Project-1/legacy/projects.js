const projects = [
{
    title: "AMD Media Assistant",
    description: (`
    <p>AMD Media Assistant is a Media assistant for people with severe&nbsp;
        age-related macular degeneration&nbsp;
        <a href="https://my.clevelandclinic.org/health/diseases/15246-macular-degeneration" className="fancy-link">(AMD)</a>.</p>
    <p>I built it for Dr. Ravi Thyagarajan's father, who suffers from severe AMD.
        As a result, he cannot read, let alone see any user interface more complex than a few colored rectangles.</p>
    <p>AMD Media Assistant reads articles scraped from the internet while providing a simple UI such that people with impared vision can control it.
        In addition, it exposes an external dashboard so a caretaker can configure websites targeted and other various settings.</p>
    `),
    // image: "ravi2.JPG",
    code: "https://github.com/Juicestus/amd-media-assistant",
},
{
    title: (`Visual Studio Code Open In Browser`),
    description: (`
    <p>This extension does exactly what it sounds like, opens a file or resource in your browser with just one click from VS Code.</p>
    <p>Although I am not the original author, I have been the maintainer for the past three-ish years. The extension has 11.5 million downloads.</p>

    `),
    // image: "https://camo.githubusercontent.com/af25454907b3b73b7e5cdd85f506e79781f9e82f892180d7edd48c9ac3198fea/68747470733a2f2f692e6c6f6c692e6e65742f323031382f30382f31322f356236666238663337386538622e6a7067",
    code: "https://github.com/SudoKillMe/vscode-extensions-open-in-browser",
    demo: "https://marketplace.visualstudio.com/items?itemName=techer.open-in-browser",
    customDemoText: "Download"
},
{
    title: (`AI Python Tutor`),
    description: (`<p>Placed 1st at HowdyHack, the Texas A&M Fall Hackathon, sponsored by AWS, Arm, and Capital One. This project is an AI-powered Python education software using LLM assistants to generate dynamic
    content curated to the student’s progress and to analyze student’s responses to give constructive
    feedback</p>`),
    code: "https://github.com/juicestus/howdyhack",
    demo: "https://howdyhack.netlify.app/",
},
{
    title: (`Pokerbot`),
    description: (`<p>Place 3rd in the Texas A&M Computing Society&nbsp;Pokerbot Competition sponsored by&nbsp;
    Susquehanna Int. Group,&nbsp;
    Hudson River Trading,&nbsp;
    Qualcomm, and Notion. </p>`),
    code: "https://github.com/Juicestus/Pokerbot",
},
{
    title: (`RARS: RISC-V Assembler and Runtime Simulator`),
    description: (`
    <p>RARS, the RISC-V Assembler, Simulator, and Runtime, will assemble and simulate the execution of RISC-V assembly language programs. Its primary goal is to be an effective development environment for people getting started with RISC-V.</p>
    <p>I contributed to this project while I was in high school. I worked mostly on MacOS support, UI-fixes, and improving the build system. </p>
    `),
    code: "https://github.com/TheThirdOne/rars"
},
{
    title: (`OpenHands`),
    description: (`
    <p>OpenHands (formerly OpenDevin), a platform for software development agents powered by AI.</p>
    <p>OpenHands agents can do anything a human developer can: modify code, run commands, browse the web, call APIs, and yes—even copy code snippets from StackOverflow.</p>
    <p>This project was built as a response to Devin, the closed source "AI software engineer," which didn't really work.</p>
    <p>I contributed some UI QOL features with the code editor segment</p>
    `),
    code: "https://github.com/All-Hands-AI/OpenHands",
    demo: "https://all-hands.dev/"
},

{
    title: (`eXTendable C++`),
    description: (`<p>Compiler/interpreter for my JavaScript-like custom programming language, designed to be easily extendable with C++.</p>`),
    code: "https://github.com/Juicestus/extendable"
},
{
    title: (`Calc (bc++)`),
    description: (`<p>Originally a clone of the Unix bc (basic-calculator) utility. I added a number of additional features on top of the original spec for more advanced calculations, along with control flow components, making it turing-complete.</p>`),
    code: "https://github.com/Juicestus/calc"
},
{
    title: (`cmath`),
    description: (`<p>From-scratch implementation of the C standard library functions available in the math.h header.</p>`),
    code: "https://github.com/Juicestus/cmath"
},
{
    title: (`TorqueTask`),
    description: (`<p>A free, open source, web-based task management system, similar to Jira, for FIRST Robotics Teams.</p>`),
    code: "https://github.com/TexasTorque/TorqueTask",
    demo: "https://task.texastorque.org",
},
{
    title: (`Formula SAE Fast Telemetry Proxy`),
    description: (`<p>A fast telemetry proxy for on-vehicle CAN network, built for the Texas A&M Formula Electric racing team.</p>`),
    code: "https://github.com/TAMU-Formula-SAE-EV/TelemetryCore",
},
{
    title: (`TorqueLearn`),
    description: (`<p>An open source aggregation of FRC knowledge to accelerate the induction of new members and maintain a consistent knowledgebase.</p>`),
    code: "https://github.com/TexasTorque/TorqueLearn",
},

];
const projectsArea = document.getElementById("projects-area");

let inner = "";
for (const project of projects) {

    inner += `<h3>${project.title}</h3>`;
    inner += project.description;
    if (project.code ) {
        inner += `<p><a href="${project.code}">Source Code</a>`;
    }
    if (project.demo ) {
        const demoText = project.customDemoText ? project.customDemoText : "Live Demo";
        inner += ` | <a href="${project.demo}">${demoText}</a>`;
    }
}

projectsArea.innerHTML = inner;