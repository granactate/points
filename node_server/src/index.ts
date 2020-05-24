import path from "path";
import express from "express";

import { Bot } from './interfaces/Data';

import { ReaderController } from "./controllers/Reader";
import { ProcessorController } from "./controllers/Processor";

const app = express();
const port = 8080; // default port to listen

app.use('/public',express.static(path.join(__dirname, 'public')));
app.set("views", path.join(__dirname, "views"));
app.set("view engine", "ejs");


// define a route handler for the default home page
app.get("/", (req: express.Request, res: express.Response) => {
    const reader = new ReaderController();
    const processor = new ProcessorController();
    const files: string[] = reader.readInfo();
    const regex = /gen_([0-9]+).json/;

    const generationId = parseInt(regex.exec(files[0])[1], 10);
    const bestInGeneration: Bot = reader.getBestBot(generationId);

    const parent = processor.trackingBot(bestInGeneration, generationId);
    const stackParents = [parent];
    let generation = generationId - 1 ;

    while (generation > 0) {
      const before = stackParents[stackParents.length - 1];
      stackParents.push(processor.trackingBot(before, generation));
      generation--;
    }
    const data = JSON.stringify(stackParents.reverse());


    res.render("index", {files, data});
});

// start the Express server
app.listen(port, () => {
    console.log(`server started at http://localhost:${port}`);
});
