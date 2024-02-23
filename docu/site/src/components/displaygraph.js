import React, {useEffect, useState} from 'react';
import { animated, SpringValue, useSprings } from '@react-spring/web'
import { useDrag } from '@use-gesture/react'
/*
graph = {"v": ['a', 'b', 'c'], "e": [[0, 1], [1, 2]]} 
loc = [[0, 0], [0, 1], [0, 2]]
*/

const ComputeVertexLocations = (graph) => {
  var loc = []
  var n = graph['v'].length
  var m = graph['e'].length
  var i;
  for (i = 0; i < n; i++) {
    loc.push([i, 0])
  }
  return loc
}

const make_path = (x, y) => `M ${x-25},${y}
a 25,25 0 1,1 50, 0
a 25,25 0 1 ,1 -50, 0
`;

const make_curve = (val, isloop, ax, ay, bx, by) => {
  //if (val === 0) return ``;
  var r = 25;
  var theta=25*Math.PI/180;
  if (isloop) {
    var aax = ax+r*Math.cos(Math.PI/2-theta)
    var aay = ay-r*Math.sin(Math.PI/2-theta)
    var bbx = bx+r*Math.cos(Math.PI/2+theta)
    var bby = by-r*Math.sin(Math.PI/2+theta)

    var x1 = ax + r * 4.5 * Math.cos(Math.PI/2-theta);
    var y1 = ay - r * 4.5 * Math.sin(Math.PI/2-theta);
    var x2 = ax + r * 4.5 * Math.cos(Math.PI/2+theta);
    var y2 = ay - r * 4.5 * Math.sin(Math.PI/2+theta);
    
    return `M ${aax} ${aay}
    C ${x1} ${y1}, ${x2} ${y2}, ${bbx} ${bby} 
    L ${bbx + r/2*Math.cos(Math.PI/2)} ${bby - r/2*Math.sin(Math.PI/2)}
    M ${bbx} ${bby}
    L ${bbx + r/2*Math.cos(Math.PI/2 + 2*theta)} ${bby - r/2*Math.sin(Math.PI/2+2*theta)}`;
  } else {

    var mx = (ax + bx) / 2;
    var my = (ay + by) / 2;
    var tx = - (by - ay) / 2 * Math.sin(1.2*theta);
    var ty = + (bx - ax) / 2 * Math.sin(1.2*theta);

    var t0 = Math.atan2(-(by - ay), bx - ax);
    // var aax = ax+r*Math.cos(t0 - theta);
    // var aay = ay-r*Math.sin(t0 - theta);
    // var bbx = bx+r*Math.cos(t0 + theta + Math.PI);
    // var bby = by-r*Math.sin(t0 + theta + Math.PI);
    var aax = ax+r*Math.cos(t0);
    var aay = ay-r*Math.sin(t0);
    var bbx = bx+r*Math.cos(t0 + Math.PI);
    var bby = by-r*Math.sin(t0 + Math.PI);


    return `M ${aax} ${aay} L ${bbx} ${bby}`;
    return `M ${aax} ${aay} 
    Q ${mx+tx} ${my+ty}, ${bbx} ${bby}
    L ${bbx - r/2*Math.cos(t0)} ${bby + r/2*Math.sin(t0)}
    M ${bbx} ${bby}
    L ${bbx - r/2*Math.cos(t0 + 2*theta)} ${bby + r/2*Math.sin(t0 + 2*theta)}
    `;
  }
}

export const DisplayAnchoredGraph = ({ graph, loc, setLocFn }) => {
  const nodes = graph['v'].map((name, idx) => {
    var cx = loc[idx][0]*50 + 100;
    var cy = loc[idx][1]*50 + 100;
    return (
    <g key={idx}>
      <circle cx={cx} cy={cy} r={20} strokeWidth="2" stroke="black" fill="#FFC" />
      <text x={cx} y={cy} textAnchor='middle' dominantBaseline='middle'>{name}</text>
    </g>
  )});
  var n = graph['v'].length;
  var m = graph['e'].length;
  var [coordsStr, setCoordsStr] = useState("");
  var [coords, api] = useSprings(n, (i) => ({
      x: 50 + i * 600/n,
      y: 100,
      d: make_path(50 + i * 600/n, 100),
      onRest: () => {
        var output = [];
        for (var j = 0; j < n; j++) output.push([coords[j].x, coords[j].y]);
        setCoordsStr(JSON.stringify(output));
      }
  }), [graph])
  var [edges, api2] = useSprings(m, (eid) => {
    var i = graph['e'][eid][0]
    var j = graph['e'][eid][1]
    var val = graph['e'][eid].length > 2? graph['e'][eid][2]: 1;

    return {
      val: val,
      stroke: `rgba(48, 48, 48, 0.9)`,
      d: make_curve(val, i===j,
        coords[i].x.get(),
        coords[i].y.get(),
        coords[j].x.get(),
        coords[j].y.get())
    }
  }, [coords])

  

  const fn = (targetIdx, nx, ny, nd, down) => (i) => (
    i === targetIdx
    ? {
        x: nx,
        y: ny,
        d: nd,
        immediate: down
      }
    : {
        x: coords[i].x.goal,
        y: coords[i].y.goal,
        d: coords[i].d.goal,
        immediate: down
      }
  );

  const fn2 = (targetIdx, nx, ny, down) =>
  (eid) => {
    var i = graph['e'][eid][0];
    var j = graph['e'][eid][1];
    var val = graph['e'][eid].length > 2? graph['e'][eid][2]: 1;
    
    return {
      val: val,
      stroke: `rgba(48, 48, 48, ${val})`,
      d: make_curve(val, i===j,
        (i===targetIdx? nx : coords[i].x.goal),
        (i===targetIdx? ny : coords[i].y.goal),
        (j===targetIdx? nx : coords[j].x.goal),
        (j===targetIdx? ny : coords[j].y.goal)),
      immediate: down,
    }
  };

  var bind = useDrag((e) => {
    var i = e.args[0]
    var down = e.down
    var mx = e.delta[0]
    var my = e.delta[1]
    if (mx === 0 && my === 0) return;
    var nx = coords[i].x.goal + mx 
    var ny = coords[i].y.goal + my
    var nd = make_path(nx, ny)
    api.start(fn(i, nx, ny, nd, down))
    api2.start(fn2(i, nx, ny, down))
  });


  
  var objs = []
  for (var eid = 0; eid < m; eid++) {
    var d = edges[eid].d
    var stroke = edges[eid].stroke
    objs.push((
      <g key={n+eid}>
        <animated.path d={d}
        stroke={stroke} strokeWidth="5px" 
        strokeLinecap="round"
        fill="none" 
        />
      </g>
    ))
  }
  for (var i = 0; i < n; i++) {
    var x = coords[i].x
    var y = coords[i].y
    var d = coords[i].d
    //coords.map(({ x, y, d }, i) => 
    objs.push((
    <g key={i}><animated.path d={d}
    stroke="#333" strokeWidth="5px" 
    fill={"#FFF"}
    {...bind(i)}
    />
    <animated.text x={x} y={y} className="svgtext" dominantBaseline="middle" textAnchor="middle" style={{fontSize:"150%",
     pointerEvents: "none"}}
    >{graph['v'][i]||i}</animated.text>
    </g>
    ));
    }
  
  return (<div>
    {JSON.stringify(loc)}
    {JSON.stringify(graph)}
    <svg width="100%" height="400" viewBox="0 0 600 400" version="1.1" xmlns="http://www.w3.org/2000/svg" 
  xmlnsXlink="http://www.w3.org/1999/xlink">
    {objs}
  </svg>
  <div>{coordsStr}</div>
    </div>
  )
}



export const ListAllMincuts = ({graph}) => {
  const [msg, updateMsg] = useState("");
  const [start, setStart] = useState(true);
  const [workcount, setWorkcount] = useState(0);
  const [currentCounter, setCurrentCounter] = useState(1);
  const [currentMincutValue, setCurrentMincutValue] = useState(Infinity);

  const expressCounter = (counter) => {
    var subset = [];
    var vid = 0;
    while (counter > 0) {
      if (counter % 2 !== 0) {
        subset.push(vid);
      }
      vid += 1;
      counter = Math.floor(counter / 2);
    }
    return JSON.stringify(subset);
  }

  useEffect(() => {
    if (start === false) return;
    setWorkcount(w => w+1);

    var n = graph['v'].length;
    var m = graph['e'].length;
    var work = 0;
    var counter = currentCounter;
    while (work < 1000 && counter < (1<<n) - 1) {
      var cutvalue = 0
      for (var i = 0; i < m; i++) {
        var u = graph['e'][i][0]
        var v = graph['e'][i][1]
        var w = graph['e'][i].length > 2? graph['e'][i][2] : 1
        if ((!!(counter&(1<<u))) != (!!(counter&(1<<v)))) {
          cutvalue += w;
        }
      }
      if (cutvalue < currentMincutValue) {
        updateMsg("");
        setCurrentCounter(counter);
        setCurrentMincutValue(cutvalue);
        return;
      } else if (cutvalue === currentMincutValue) {
        updateMsg(msg + "\n" + expressCounter(counter));
        setCurrentCounter(counter + 1);
        return;
      }
      work++;
      counter++;
    }

    if (counter >= (1<<n) - 1) {
      setStart(false);
      setCurrentCounter(counter);
      return;
    }
    setCurrentCounter(counter);
  }, [workcount]);

  return (<div>
    n = {graph['v'].length}<br/>
    counter = {currentCounter}<br/>
    mincutvalue = {currentMincutValue} <br/>
    {msg}
  </div>);
}

export default function DisplayGraph({ graph }) {
  var [loc, setLoc] = useState(ComputeVertexLocations(graph));
  return (<DisplayAnchoredGraph graph={graph} loc={loc} setLocFn={setLoc} />);
}